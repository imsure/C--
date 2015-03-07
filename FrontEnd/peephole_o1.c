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

void peephole_o1( TAC_seq *tacseq )
{
  collapse_constant_assg( tacseq );
  transform_cond_jump( tacseq );
}
