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

int num_defuses = 0; // total number of definitions inside the current processed function.
extern bbl *bhead; // header to the basic block list of the current function.

static bool debug = false;

/**
 * Compute the total number of possbile definitions/uses of local
 * variables/tmps in the TAC sequence 'tacseq' for a producedure/function.
 *
 * The value returned will be the size of the bitvector used
 * for computing reaching definition.
 */
static int func_num_defuses( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  int def_counter = 0;

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ||
	 tac->optype == Retrieve || tac->optype == Param ||
	 is_relational_op(tac->optype) || tac->optype == Return ) {
	tac->id = ++def_counter;
    }
    tac = tac->next;
  }

  return def_counter;
}

void compute_num_defuses( TAC_seq *tacseq )
{
  num_defuses = func_num_defuses( tacseq );
}

/**
 * Compute the set of definitions for each local variables/tmps.
 * The results are stored in the their symbol table entries.
 */
static void compute_defset_locals( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;

  //  compute_num_defuses( tacseq );

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ||
	 tac->optype == Retrieve ) {
      if ( is_valid_local(tac->dest) ) {
	if ( tac->dest->val.stptr->bv == NULL ) {
	  tac->dest->val.stptr->bv = NEW_BV( num_defuses-1 );
	}
	if ( debug ) {
	  printf( "set %d to bit vec of %s\n", tac->id, tac->dest->val.stptr->name );
	}
	SET_BIT( tac->dest->val.stptr->bv, tac->id-1 );
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
  int iternum = 0;

  while ( iternum < bb->numtacs ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ||
	 tac->optype == Retrieve ) {
      if ( is_valid_local(tac->dest) ) {
	bvtmp = bb->gen;
	bb->gen = bv_diff( bb->gen, tac->dest->val.stptr->bv, num_defuses-1 );
	free( bvtmp );
	SET_BIT( bb->gen, tac->id-1 );

	bvtmp = bb->kill;
	bb->kill = bv_union( bb->kill, tac->dest->val.stptr->bv, num_defuses-1 );
	free( bvtmp );
	CLEAR_BIT( bb->kill, tac->id-1 );
      }
    }
    tac = tac->next;
    ++iternum;
  }

  /* if ( strcmp(bb->first_tac->dest->val.label, "_L11") == 0 ) { */
  /*   print_bv( "Gen set for _L11", bb->gen, num_defuses-1 ); */
  /*   print_bv( "Kill set for _L11", bb->kill, num_defuses-1 ); */
  /* } */
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
    bbl_run->gen = NEW_BV( num_defuses-1 );
    bbl_run->kill = NEW_BV( num_defuses-1 );
    compute_genkill_bb( bbl_run );
    bbl_run = bbl_run->next;
  }
}

/**
 * Compute the in set for the basic block 'bb'.
 * bb.in = union of in sets of all predecessor of bb.
 */
static bitvec *compute_inset_bb( bbl *bb )
{
  bitvec *bvtmp;
  bitvec *res = NEW_BV( num_defuses-1 );
  control_flow_list *cfl = bb->pred;
  
  while ( cfl != NULL ) {
    bvtmp = res;
    res = bv_union( res, cfl->bb->out, num_defuses-1 );
    free( bvtmp );
    cfl = cfl->next;
  }

  /* if ( strcmp(bb->first_tac->dest->val.label, "_L11") == 0 ) { */
  /*   print_bv( "In set for _L11", res, num_defuses-1 ); */
  /* } */

  return res;
}

/**
 * Compute the out set for the basic block 'bb'.
 * bb.out = bb.gen union (bb.in - bb.kill)
 */
static bitvec *compute_outset_bb( bbl *bb )
{
  bitvec *bvtmp;
  bitvec *res;
  
  res = bv_diff( bb->in, bb->kill, num_defuses-1 );
  bvtmp = res;
  res = bv_union( res, bb->gen, num_defuses-1 );
  free( bvtmp );
  return res;
}

/**
 * Compute in and out set for each basic block of the current
 * processed function.
 */
static void compute_inout()
{
  bbl *bbl_run;
  bitvec *bvtmp, *oldout, *oldin;
  bool change;

  /* Initialize in and out set for each basic block. */
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    bbl_run->in = NEW_BV( num_defuses-1 );
    bbl_run->out = NEW_BV( num_defuses-1 );
    bvtmp = bbl_run->out;
    bbl_run->out = bv_union( bbl_run->out, bbl_run->gen, num_defuses-1 );
    free( bvtmp );
    bbl_run = bbl_run->next;
  }

  /* Iteratively compute in and out set until they converge. */
  change = true;
  while ( change ) {
    //    printf( "Computing inout: iteration %d\n", iter_num++ );
    change = false;
    bbl_run = bhead;
    while( bbl_run != NULL ) {
      oldin = bbl_run->in;
      bbl_run->in = compute_inset_bb( bbl_run );
      oldout = bbl_run->out;
      bbl_run->out = compute_outset_bb( bbl_run );
      if ( bv_unequal_check(oldout, bbl_run->out, num_defuses-1) == true ||
	   bv_unequal_check(oldin, bbl_run->in, num_defuses-1) == true ) {
	//	printf( "Iteration %d: change is true\n", iter_num );
	change = true;
      }
      free( oldin );
      free( oldout );
      bbl_run = bbl_run->next;
    }
  }
  //  printf( "Converge!\n" );  
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
		  tac->dest->val.stptr->bv, num_defuses-1 );
      }
    } else if (tac->optype == Retrieve) {
      if ( tac->operand1->val.stptr->scope == Local ) {
	print_bv( tac->operand1->val.stptr->name,
		  tac->operand1->val.stptr->bv, num_defuses-1 );
      }
    }
    tac = tac->next;
  }
}   

void reaching_defs( TAC_seq *tacseq )
{
  compute_defset_locals( tacseq );
  compute_genkill();
  compute_inout();
  //  print_var_defs( tacseq );
}
