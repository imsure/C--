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

int num_defs; // total number of definitions inside the current processed function.
extern bbl *bhead; // header to the basic block list of the current function.

/**
 * Compute the number of the definitions (only apply for locals)
 * in the TAC sequence 'tacseq' for a producedure/function.
 *
 * The value returned will be the size of the bitvector used
 * for computing reaching definition.
 */
static int func_num_defs( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  int def_counter = 0;

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ) {
      if ( tac->dest->val.stptr->scope == Local ) {
	tac->def_num = ++def_counter;
      }
    } else if (tac->optype == Retrieve) {
      if ( tac->operand1->val.stptr->scope == Local ) {
	tac->def_num = ++def_counter;
      }
    }
    tac = tac->next;
  }

  return def_counter;
}

static void compute_defset_locals( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  num_defs = func_num_defs( tacseq );
  printf( "Number of defs: %d\n", num_defs );

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ) {
      if ( tac->dest->val.stptr->scope == Local ) {
	if ( tac->dest->val.stptr->bv == NULL ) {
	  tac->dest->val.stptr->bv = NEW_BV( num_defs-1 );
	}
	//printf( "set %d to bit vec of %s\n", tac->def_num, tac->dest->val.stptr->name );		
	SET_BIT( tac->dest->val.stptr->bv, tac->def_num-1 );
      }
    } else if (tac->optype == Retrieve) {
      if ( tac->operand1->val.stptr->scope == Local ) {
	if ( tac->operand1->val.stptr->bv == NULL ) {
	  tac->operand1->val.stptr->bv = NEW_BV( num_defs-1 );
	}
	SET_BIT( tac->operand1->val.stptr->bv, tac->def_num-1 );
      }
    }
    tac = tac->next;
  }
}

/**
 * Compute gen and kill set for the basic block 'bb'
 * using its local information.
 */

static void compute_genkill_bb( bbl *bb )
{
  TAC *tac = bb->first_tac;
  bitvec *bvtmp;

  while ( tac != bb->last_tac ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ||
	 tac->optype == Retrieve ) {
      if ( tac->dest->val.stptr->scope == Local ) {
	bvtmp = bb->gen;
	bb->gen = bv_diff( bb->gen, tac->dest->val.stptr->bv, num_defs-1 );
	free( bvtmp );
	SET_BIT( bb->gen, tac->def_num-1 );

	bvtmp = bb->kill;
	bb->kill = bv_union( bb->kill, tac->dest->val.stptr->bv, num_defs-1 );
	free( bvtmp );
	CLEAR_BIT( bb->kill, tac->def_num-1 );
      }
    }
    tac = tac->next;
  }

  /* One more iteration for the last tac. */
  if ( is_arith_op(tac->optype) || tac->optype == Assg ||
       tac->optype == Retrieve ) {
    if ( tac->dest->val.stptr->scope == Local ) {
      bvtmp = bb->gen;
      bb->gen = bv_diff( bb->gen, tac->dest->val.stptr->bv, num_defs-1 );
      free( bvtmp );
      SET_BIT( bb->gen, tac->def_num-1 );

      bvtmp = bb->kill;
      bb->kill = bv_union( bb->kill, tac->dest->val.stptr->bv, num_defs-1 );
      free( bvtmp );
      CLEAR_BIT( bb->kill, tac->def_num-1 );
    }
  }
}

/**
 * Compute gen and kill set for each basic block of the current
 * processed function.
 */
static void compute_genkill()
{
  bbl *bbl_run;
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    bbl_run->gen = NEW_BV( num_defs-1 );
    bbl_run->kill = NEW_BV( num_defs-1 );
    compute_genkill_bb( bbl_run );
    bbl_run = bbl_run->next;
  }
}

/**
 * Compute in and out set for each basic block of the current
 * processed function.
 */
static void compute_inout()
{
  bbl *bbl_run;
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    bbl_run->gen = NEW_BV( num_defs-1 );
    bbl_run->kill = NEW_BV( num_defs-1 );
    compute_genkill_bb( bbl_run );
    bbl_run = bbl_run->next;
  }
}


/*************************************
 * For debug purpose:
 ************************************/
void print_var_defs( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ) {
      if ( tac->dest->val.stptr->scope == Local ) {
	print_bv( tac->dest->val.stptr->name,
		  tac->dest->val.stptr->bv, num_defs-1 );
      }
    } else if (tac->optype == Retrieve) {
      if ( tac->operand1->val.stptr->scope == Local ) {
	print_bv( tac->operand1->val.stptr->name,
		  tac->operand1->val.stptr->bv, num_defs-1 );
      }
    }
    tac = tac->next;
  }
}   

void reaching_defs( TAC_seq *tacseq )
{
  compute_defset_locals( tacseq );
  compute_genkill();
  //print_var_defs( tacseq );
}
