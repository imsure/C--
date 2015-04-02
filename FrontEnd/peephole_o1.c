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
#include "basic_block.h"

extern label_list *lhead;

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
	     tac_next->operand1->val.stptr == tac->dest->val.stptr ) { // must point to the same symbol table entry
	  /* Modify 'tac_next' to get rid of 'tac' which is redundant.
	     Turn its operand1 into a constant. */
	  tac_next->operand1 = tac->operand1;

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
void transform_cond_jump( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  TAC *tac_next, *tac_next_next;

  /* Forward traversing */
  while ( tac != NULL ) {
    if ( is_relational_op(tac->optype) == true ) {
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
static void precompute_constant_arrayindex( TAC_seq *tacseq )
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
	   tac_next_next->dest->val.stptr->type == t_Tmp_Addr &&
	   tac_next_next->operand1->val.stptr->type == t_Array ) { // t_Array always appear as operand1
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
void delete_redundant_jump( TAC_seq *tacseq )
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

/**
 * Look up the final destination for the goto statement 'start_tac'
 * given a list of compiler generated labels.
 */
static TAC *lookup_dest( TAC *start_tac, label_list *llist_head )
{
  label_list *llist_run = llist_head->next_label;
  TAC *tac_next;
  
  while ( llist_run != NULL ) {
    if ( strcmp(llist_run->mylabel->dest->val.label,
		start_tac->dest->val.label) == 0 ) {
      tac_next = llist_run->mylabel->next;
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
  label_list *llist_head = lhead;

  tac = tacseq->start; // reset to the beginning
  while ( tac != NULL ) {
    if ( tac->optype == Goto || is_relational_op(tac->optype) == true ) {
      tac_dest = lookup_dest( tac, llist_head );
      if ( tac != tac_dest ) { // update goto dest
	tac->dest = tac_dest->dest;
      }
    }
    tac = tac->next;
  }
}

/**
 * This is called after removing redundant labels, like:
 * L1:
 * L2:
 *   ...
 *
 * After L1 is removed, there might be some jump instructions that 
 * still goto L1, we need to update labels for these instruction so
 * that they now goto L2 instead.
 *
 * 'dest_old' is removed label and 'dest_new' is its replacement.
 */
static void update_jump_dest( TAC_seq *tacseq,
			      address *dest_old,
			      address *dest_new )
{
  TAC *tac;
  
  tac = tacseq->start;
  while ( tac != NULL ) {
    if ( is_relational_op(tac->optype) == true ||
	 tac->optype == Goto ) {
      if ( tac->dest == dest_old ) {
	tac->dest = dest_new;
	//printf( "dest %s has been replaced by dest %s.\n",
	//	dest_old->val.label, dest_new->val.label );
      }
    }
    tac = tac->next;
  }  
}

/**
 * Peephole optimization: collapse label chain.
 *
 * For exmaple:
 *     ...
 * L1:
 * L2:
 *     ...
 * can be optimized as:
 * L2:
 *
 * to delete an unnecessary label L1.
 *
 * Note this function should be called after
 * transform_cond_jump() and delete_redundant_jump() to guarantee that
 * there will be no statement that jumps to L1 in the TAC sequence.
 *
 * NOTE:
 * the above claim is not true, becuase the test case:
 * Tests/unittest/reg_alloc/simple_while.c
 * reveals that there could still be statements that jump to the removed label,
 * so we need to take care of that!
 */
void collapse_label_chain( TAC_seq *tacseq )
{
  TAC *tac, *tactmp;
  
  tac = tacseq->start; // reset to the beginning
  while ( tac != NULL ) {
    if ( tac->optype == Label && tac->next->optype == Label ) {
      tac->prev->next = tac->next;
      tac->next->prev = tac->prev;
      update_jump_dest( tacseq, tac->dest, tac->next->dest );
      tactmp = tac;
      tac = tac->next;
      free( tactmp );
      continue;
    }
    tac = tac->next;
  }
}

static int calculate( SyntaxNodeType optype, int v1, int v2 )
{
  switch ( optype ) {
  case Plus:
    return v1+v2;
  case BinaryMinus:
    return v1-v2;
  case Mult:
    return v1*v2;
  case Div:
    return v1/v2;
  default:
    return 0;
  }
}

/**
 * Pre-calculate constant arithmetic like: x = 4 * 7 --> x = 28
 */
static void collapse_constant_arith( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  
  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) && tac->optype != UnaryMinus ) {
      if ( (tac->operand1->atype == AT_Intcon || tac->operand1->atype == AT_Charcon) &&
	   (tac->operand2->atype == AT_Intcon || tac->operand2->atype == AT_Charcon) ) {
	/* pre-caculate the value. */
	tac->operand1->val.iconst = calculate( tac->optype,
					       tac->operand1->val.iconst,
					       tac->operand2->val.iconst );
	tac->optype = Assg; // change optype
	tac->operand2 = NULL;
      }
    }
    tac = tac->next;
  }
}

/**
 * Peephole optimization: stage 1.
 * This is done before copy propagation and dead code elimination.
 */
void peephole_stage1( TAC_seq *tacseq )
{
  collapse_constant_assg( tacseq );
  transform_cond_jump( tacseq );
  precompute_constant_arrayindex( tacseq );
  delete_redundant_jump( tacseq );
  collapse_jump_chain( tacseq );
  collapse_label_chain( tacseq );
  collapse_constant_arith( tacseq );
}

/**
 * Peephole optimization: stage 2.
 * This is done after copy propagation and dead code elimination.
 */
void peephole_stage2( TAC_seq *tacseq )
{
  collapse_constant_arith( tacseq );
}

