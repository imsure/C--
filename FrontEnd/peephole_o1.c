/**
 * Implementation of peephole optimization.
 * Effective when the comipler is invoked with -O1 option.
 * *******************************************************
 *
 * Author: Shuo Yang
 * Email: imsure95@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "protos.h"
#include "syntax-tree.h"

/**
 * Linked list of compiler generated labels.
 */
typedef struct Label_List {
  TAC *mylabel;
  struct Label_List *next_label;
} label_list;

label_list *lhead;

/**
 * Peephole optimization: collapse constant assignment.
 *
 * For exmaple:
 * C: 
 * x = 5;
 *
 * translated as:
 *
 * TAC:
 * _tvar0 = 5
 * x = _tvar0
 *
 * can be optimized as:
 * x = 5
 * without going through a redundant tmp variable.
 *
 * So given a TAC sequence, we traverse it forward, identify
 * consecutive seuquence of pairs that are assigning constant
 * to a tmp variable, then assigning the tmp variable back to a
 * local/formal/global variable.
 */
static void collapse_constant_assg( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  TAC *tac_next, *tac_prev;

  /* Forward traversing */
  while ( tac != NULL ) {
    /* First, identify if 'tac' is an assignemnt that
       assigns a constant value to a tmp variable like "_tvar0 = 123" */
    if ( tac->optype == Assg &&
	 (tac->operand1->atype == AT_Intcon ||
	  tac->operand1->atype == AT_Charcon) &&
	 tac->dest->val.stptr->type == t_Tmp_Var ) { // if all true, we found one
      /* Then identify the next TAC. */
      tac_next = tac->next;
      if ( tac_next != NULL && tac_next->optype == Assg ) {
	if ( tac_next->operand1->atype == AT_StRef &&
	     strcmp(tac_next->operand1->val.stptr->name,
		    tac->dest->val.stptr->name) == 0 ) { // names must match
	  /* Modify 'tac_next' to get rid of 'tac' which is redundant.
	     Turn its operand1 into a constant. */
	  tac_next->operand1->atype = tac->operand1->atype;
	  tac_next->operand1->val.iconst = tac->operand1->val.iconst;

	  tac_prev = tac->prev; // in this case, tac->prev must not be NULL
	  tac_prev->next = tac_next;
	  tac_next->prev = tac_prev;

	  free( tac );
	  /* 2 step forward. */
	  tac = tac_next->next;
	  continue;
	}
      }
    }
    tac = tac->next;
  }
}

/**
 * Check whether the given 'optype' is a relational operation.
 */
static bool is_relational( SyntaxNodeType optype )
{
  switch ( optype ) {
  case Equals:
  case Neq:
  case Leq:
  case Lt:
  case Geq:
  case Gt:
    return true;
  default:
    return false;
  }
}

/**
 * Return the reverse of the relational operation 'optype'.
 */
static SyntaxNodeType reverse_relational_optype( SyntaxNodeType optype )
{
  switch ( optype ) {
  case Equals:
    return Neq;
  case Neq:
    return Equals;
  case Leq:
    return Gt;
  case Lt:
    return Geq;
  case Geq:
    return Lt;
  case Gt:
    return Leq;
  default:
    return Error;
  }  
}

/**
 * Peephole optimization: transform sequence of conditional jumps.
 *
 * TAC:
 *     if x > y goto L1
 *     goto L2
 * L1:
 *     ...
 *
 * can be optimized as:
 *     if x <= y goto L2
 * L1:
 *     ...
 *
 * to reduce a goto statement.
 *
 * So given a TAC sequence, we traverse it forward, identify
 * the pattern.
 */
static void transform_cond_jump( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  TAC *tac_next, *tac_next_next;

  /* Forward traversing */
  while ( tac != NULL ) {
    if ( is_relational(tac->optype) == true ) {
      tac_next_next = tac->next->next; // should be a label
      if ( strcmp(tac->dest->val.label, tac_next_next->dest->val.label) == 0 ) {
	/* A match found */
	tac_next = tac->next;
	tac->dest = tac_next->dest; // change goto destination
	tac->optype = reverse_relational_optype( tac->optype ); // reverse optype

	tac->next = tac_next_next; // chain tac and tac_next_next
	tac_next_next->prev = tac; // chain tac and tac_next_next

	free( tac_next ); // free redudant goto instruction
	tac = tac->next->next; // two step forward
	continue;
      }
    }
    tac = tac->next;
  }  
}

/**
 * Peephole optimization: transform array reference that is in the
 * form of A[2] where the index is a constant.
 *
 * TAC:
 * _tvar0 = 2 
 * _tvar0 = _tvar0 * 4 
 * _taddr2 = A + _tvar0
 *
 * can be optimized as:
 * _taddr2 = A + 8
 * 
 * to remove redudant calculation.
 *
 * So given a TAC sequence, we traverse it forward, identify
 * the pattern.
 */
static void transform_array_ref( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  TAC *tac_next, *tac_next_next, *tac_prev;
  int offset;

  /* Forward traversing */
  while ( tac != NULL ) {
    /* First, identify if 'tac' is an assignemnt that
       assigns a constant value to a tmp variable like "_tvar0 = 2" */
    if ( tac->optype == Assg &&
	 (tac->operand1->atype == AT_Intcon ||
	  tac->operand1->atype == AT_Charcon) &&
	 tac->dest->val.stptr->type == t_Tmp_Var ) { // if all true, we found one
      /* Then check if the next next instruction is: _taddr2 = A + _tvar0. */
      tac_next_next = tac->next->next;
      if ( tac_next_next->optype == Plus &&
	   tac_next_next->dest->val.stptr->type == t_Tmp_Addr ) {
	/* A match found, directly calculate the offset of the array element. */
	tac_next = tac->next; // tac_next must be: _tvar0 = _tvar0 * 4
	offset = tac->operand1->val.iconst * tac_next->operand2->val.iconst;
	tac_next_next->operand2->atype = AT_Intcon; // modify its operand2's type
	tac_next_next->operand2->val.iconst = offset; // fill operand2's value

	tac_prev = tac->prev;
	tac_prev->next = tac_next_next;
	tac_next_next->prev = tac_prev;

	free( tac_next );
	free( tac );

	tac = tac_next_next->next; // 3 steps forward
	continue;
      }
    }
    tac = tac->next;
  }  
}

/**
 * Peephole optimization: get rid of redundant jump.
 *
 * TAC:
 *     goto L1
 * L1:
 *     ...
 *
 * can be optimized as:
 * L1:
 *     ...
 *
 * to get rid of a redundant goto statement.
 *
 * So given a TAC sequence, we traverse it forward, identify
 * the pattern.
 */
static void delete_redundant_jump( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  TAC *tac_next, *tac_prev;

   while ( tac != NULL ) {
     if ( tac->optype == Goto ) {
       /* Check if the next TAC is a label. */
       tac_next = tac->next;
       if ( tac_next->optype == Label &&
	    strcmp(tac->dest->val.label, tac_next->dest->val.label) == 0 ) {
	 /* A matched pattern found */
	 tac_prev = tac->prev;
	 tac_prev->next = tac_next;
	 tac_next->prev = tac_prev;

	 free( tac );
	 tac = tac_next->next; // 2 step forward
	 continue;
       }
     }
     tac = tac->next;
   }
}

static TAC *lookup_dest( TAC *start_tac, label_list *llist_head )
{
  label_list *llist_run = llist_head->next_label;
  TAC *tac_next;
  
  while ( llist_run != NULL ) {
    if ( strcmp(llist_run->mylabel->dest->val.label,
		start_tac->dest->val.label) == 0 ) {
      tac_next = llist_run->mylabel->next;
      while ( tac_next->optype == Noop ) {
	tac_next = tac_next->next; // skip Noop TAC.
      }
      if ( tac_next->optype == Goto ) { // pattern found
	return lookup_dest( tac_next, llist_head );
      }
      break;
    }
    llist_run = llist_run->next_label;
  }
  return start_tac;
}

/**
 * Peephole optimization: collapse jump chain.
 *
 * For exmaple:
 *     goto L1 
 *     ...
 * L1:
 *     goto L2
 *     ...
 * L2:
 *     goto L3
 *     ...
 * L3:
 *     _tvar0 = 5 
 *
 * translated as:
 *     goto L3 
 *     ...
 * L1:
 *     goto L2
 *     ...
 * L2:
 *     goto L3
 *     ...
 * L3:
 *     _tvar0 = 5 
 *
 * so that let the first goto directly jump to its final destination
 * without going through a chain of jumps.
 *
 */
static void collapse_jump_chain( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  TAC *tac_dest;
  label_list *llist_head, *llist_run;

  llist_head = (label_list *) zalloc( sizeof(label_list) );
  llist_run = llist_head;

  /* Collect all compiler generated label instructions. */
  while ( tac != NULL ) {
    if ( tac->optype == Label && tac->operand1 == NULL ) { // omit function labels
      llist_run->next_label = (label_list *) zalloc( sizeof(label_list) );
      llist_run->next_label->mylabel = tac;
      llist_run = llist_run->next_label;
    }
    tac = tac->next;
  }

  tac = tacseq->start; // reset to the beginning
  while ( tac != NULL ) {
    if ( tac->optype == Goto || is_relational(tac->optype) == true ) {
      tac_dest = lookup_dest( tac, llist_head );
      if ( tac != tac_dest ) { // update goto dest
	tac->dest = tac_dest->dest;
      }
    }
    tac = tac->next;
  }

  lhead = llist_head; // for constructing basic block
}

void peephole_o1( TAC_seq *tacseq )
{
  collapse_constant_assg( tacseq );
  transform_cond_jump( tacseq );
  transform_array_ref( tacseq );
  delete_redundant_jump( tacseq );
  collapse_jump_chain( tacseq );
}
