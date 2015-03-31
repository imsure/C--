/**
 * A short and concise description goes here.
 * *************************************************
 *
 * Author: Shuo Yang
 * Email: imsure95@gmail.com
 */

#include "bitvector.h"
#include "protos.h"
#include "syntax-tree.h"
#include "basic_block.h"

int num_vars; // total number of variables inside the current
              // processed function. This will be the size of bit vectors.
extern bbl *bhead; // header to the basic block list of the current function.

/**
 * Check if address 'var' is a valid local variable, either
 * user defined or compiler generated tmp variables.
 */
static bool valid_local( address *var )
{
  if ( var != NULL && var->atype == AT_StRef &&
       var->val.stptr->scope == Local ) {
    return true;
  }
  return false;
}

/**
 * Count the number of the local variables and assign the ids to them
 * in the TAC sequence 'tacseq' which represents the current processed
 * producedure/function.
 *
 * Return the total number of the local variable which will be the
 * size of the bitvector used for liveness_analysis.
 */
static int count_assign_varids( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  int var_counter = 0;

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ||
	 tac->optype == Retrieve || tac->optype == Param ) {
      if ( tac->dest->val.stptr->scope == Local ) {
	if ( tac->dest->val.stptr->varid == 0 ) {
	  /* make sure only assign once for each variable. */
	  tac->dest->val.stptr->varid = ++var_counter;
	}
      }

      if ( valid_local( tac->operand1 ) == true ) {
	if ( tac->operand1->val.stptr->varid == 0 ) {
	  /* make sure only assign once for each variable. */
	  tac->operand1->val.stptr->varid = ++var_counter;
	}
      }

      if ( valid_local( tac->operand2 ) == true ) {
	if ( tac->operand2->val.stptr->varid == 0 ) {
	  /* make sure only assign once for each variable. */
	  tac->operand2->val.stptr->varid = ++var_counter;
	}
      }
    }
    tac = tac->next;
  }

  return var_counter;
}

/**
 * Compute def and use set for the basic block 'bb'
 * using its local information.
 */
static void compute_defuse_bb( bbl *bb )
{
  TAC *tac = bb->last_tac;
  bitvec *bvtmp;
  int iternum = 0;

  while ( iternum < bb->numtacs ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ) {
      if ( tac->dest->val.stptr->scope == Local ) {
	SET_BIT( bb->def, tac->dest->val.stptr->varid-1 );
	CLEAR_BIT( bb->use, tac->dest->val.stptr->varid-1 );
      }
      if ( valid_local(tac->operand1) == true ) {
	CLEAR_BIT( bb->def, tac->operand1->val.stptr->varid-1 );
	SET_BIT( bb->use, tac->operand1->val.stptr->varid-1 );
      }
      if ( valid_local(tac->operand2) == true ) {
	CLEAR_BIT( bb->def, tac->operand2->val.stptr->varid-1 );
	SET_BIT( bb->use, tac->operand2->val.stptr->varid-1 );
      }
    } else if ( tac->optype == Retrieve ) { // def
      if ( tac->dest->val.stptr->scope == Local ) {
	SET_BIT( bb->def, tac->dest->val.stptr->varid-1 );
	CLEAR_BIT( bb->use, tac->dest->val.stptr->varid-1 );
      }
    } else if ( tac->optype == Param ) { // use
      if ( tac->dest->val.stptr->scope == Local ) {
	CLEAR_BIT( bb->def, tac->dest->val.stptr->varid-1 );
	SET_BIT( bb->use, tac->dest->val.stptr->varid-1 );
      }
    }
    tac = tac->prev;
    iternum++;
  }
}

/**
 * Compute def and use set for each basic block of the current
 * processed function.
 */
static void compute_defuse()
{
  bbl *bbl_run;
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    bbl_run->def = NEW_BV( num_vars-1 );
    bbl_run->use = NEW_BV( num_vars-1 );
    compute_defuse_bb( bbl_run );
    bbl_run = bbl_run->next;
  }
}

/**
 * Compute the in set for the basic block 'bb'.
 * bb.in = union of in sets of all predecessor of bb.
 */
static bitvec *compute_inset_bb( bbl *bb )
{
}

/**
 * Compute the out set for the basic block 'bb'.
 * bb.out = bb.gen union (bb.in - bb.kill)
 */
static bitvec *compute_outset_bb( bbl *bb )
{
}

/**
 * Compute in and out set for each basic block of the current
 * processed function.
 */
static void compute_inout()
{
}

void liveness_global( TAC_seq *tacseq )
{
  num_vars = count_assign_varids( tacseq );
  compute_defuse();
}
