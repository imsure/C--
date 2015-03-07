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
	if ( tac_next->operand1.atype == AT_StRef &&
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

void peephole_o1( TAC_seq *tacseq )
{
  collapse_constant_assg( tacseq );
}
