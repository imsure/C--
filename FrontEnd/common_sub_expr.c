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

extern void printtac( TAC *tac );
extern void print_bv( const char *name, bitvec *bv, int len );

/**
 * total number of local variables/tmps
 * inside the current processed function.
 */
extern int num_vars;
/**
 * total number of definitions/uses of local vars/tmps
 * inside the current processed function.
 */
extern int num_defuses;
/**
 * header to the basic block list of the current function.
 */
extern bbl *bhead;

/**
 * The set of all expressions appearing on the RHS of some
 * instruction in the current processed procedure.
 */
bitvec *uset;

/**
 * Check if 'var' is in a valid expression.
 */
static bool is_in_valid_expr( address *var )
{
  if ( is_valid_local( var ) ||
       (var->atype == AT_Intcon || var->atype == AT_Charcon) ) {
    return true;
  }
  return false;
}

/**
 * Check if 'tac' is an instruction for calculating array adress.
 */
static bool is_array_addr_cal( TAC *tac )
{
  if ( tac->operand1->atype == AT_StRef &&
       tac->operand1->val.stptr->type == t_Array &&
       is_in_valid_expr(tac->operand2) ) {
    return true;
  }
  return false;
}

/**
 * For each local var/tmp compute the set of expressions that involve it.
 */
static void compute_expr_bv( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) ) {
      if ( tac->optype != UnaryMinus && is_array_addr_cal(tac) ) {
	/* We treat array address calculation specially. */
	SET_BIT( uset, tac->id-1 );
	if ( is_valid_local(tac->operand2) ) {
	  if ( tac->operand2->val.stptr->expr_bv == NULL ) {
	    tac->operand2->val.stptr->expr_bv = NEW_BV( num_defuses-1 );
	  }
	  printf( "add tac %d to bit vec expr_bv of %s\n", tac->id, tac->operand2->val.stptr->name );
	  SET_BIT( tac->operand2->val.stptr->expr_bv, tac->id-1 );
	}
      }

      if ( tac->optype == UnaryMinus ) {
	if ( is_valid_local(tac->operand1) ) {
	  if ( tac->operand1->val.stptr->expr_bv == NULL ) {
	    tac->operand1->val.stptr->expr_bv = NEW_BV( num_defuses-1 );
	  }
	  printf( "add tac %d to bit vec expr_bv of %s\n", tac->id, tac->operand1->val.stptr->name );
	  SET_BIT( tac->operand1->val.stptr->expr_bv, tac->id-1 );
	  SET_BIT( uset, tac->id-1 );
	}
      } else {
	if ( is_in_valid_expr(tac->operand1) && is_in_valid_expr(tac->operand2) ) {
	  if ( is_valid_local(tac->operand1) ) {
	    if ( tac->operand1->val.stptr->expr_bv == NULL ) {
	      tac->operand1->val.stptr->expr_bv = NEW_BV( num_defuses-1 );
	    }
	    printf( "add tac %d to bit vec expr_bv of %s\n", tac->id, tac->operand1->val.stptr->name );
	    SET_BIT( tac->operand1->val.stptr->expr_bv, tac->id-1 );
	  }

	  if ( is_valid_local(tac->operand2) ) {
	    if ( tac->operand2->val.stptr->expr_bv == NULL ) {
	      tac->operand2->val.stptr->expr_bv = NEW_BV( num_defuses-1 );
	    }
	    printf( "add tac %d to bit vec expr_bv of %s\n", tac->id, tac->operand2->val.stptr->name );
	    SET_BIT( tac->operand2->val.stptr->expr_bv, tac->id-1 );
	  }

	  SET_BIT( uset, tac->id-1 );
	}
      }
    }
    tac = tac->next;
  }
}

/**
 * Compute gen and kill set for the basic block 'bb'
 * using its local information.
 */
static void compute_expr_gen_kill( bbl *bb )
{
  TAC *tac = bb->first_tac;
  bitvec *bvtmp;
  int iternum = 0;

  while ( iternum < bb->numtacs ) {
    if ( is_arith_op(tac->optype) ) {
      if ( (is_valid_local(tac->operand1) && is_valid_local(tac->operand2)) ||
	   (tac->optype == UnaryMinus && is_valid_local(tac->operand1)) ) {
	SET_BIT( bb->expr_gen, tac->id-1 ); // add current tac to gen set.
	CLEAR_BIT( bb->expr_kill, tac->id-1 ); // remove current tac from kill set.
	if ( is_valid_local(tac->dest) && tac->dest->val.stptr->expr_bv ) {
	  /* current tac kills all expression involving its destination variable. */
	  bvtmp = bb->expr_gen;
	  bb->expr_gen = bv_diff( bb->expr_gen, tac->dest->val.stptr->expr_bv, num_defuses-1 );
	  free( bvtmp );
	  bvtmp = bb->expr_kill;
	  bb->expr_kill = bv_union( bb->expr_kill, tac->dest->val.stptr->expr_bv, num_defuses-1 );
	  free( bvtmp );
	}
      }
    } else if ( tac->optype == Assg || tac->optype == Retrieve ) {
      /* redefining a local var/tmp kills all expressions involving this local var/tmp. */
      if ( is_valid_local(tac->dest) && tac->dest->val.stptr->expr_bv )  {
	bvtmp = bb->expr_gen;
	bb->expr_gen = bv_diff( bb->expr_gen, tac->dest->val.stptr->expr_bv, num_defuses-1 );
	free( bvtmp );
	bvtmp = bb->expr_kill;
	bb->expr_kill = bv_union( bb->expr_kill, tac->dest->val.stptr->expr_bv, num_defuses-1 );
	free( bvtmp );
      }
    }
    //    printtac( tac );
    //    putchar( '\n' );
    tac = tac->next;
    ++iternum;
  }
}

static bitvec *compute_expr_in_bb( bbl *bb )
{
  bitvec *bvtmp;
  bitvec *res = NEW_BV( num_defuses-1 );
  control_flow_list *cfl = bb->pred;
  
  while ( cfl != NULL ) {
    bvtmp = res;
    res = bv_union( res, cfl->bb->expr_out, num_defuses-1 );
    free( bvtmp );
    cfl = cfl->next;
  }
  return res;
}

static bitvec *compute_expr_out_bb( bbl *bb )
{
  bitvec *bvtmp;
  bitvec *res;
  
  res = bv_diff( bb->expr_in, bb->expr_kill, num_defuses-1 );
  bvtmp = res;
  res = bv_union( res, bb->expr_gen, num_defuses-1 );
  free( bvtmp );
  return res;
}

/**
 * Compute in and out set for each basic block of the current
 * processed function.
 */
static void compute_expr_in_out()
{
  bbl *bbl_run;
  bitvec *bvtmp, *oldout;
  bool change;

  /* Initialize in and out set for each basic block. */
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    bbl_run->expr_in = NEW_BV( num_defuses-1 );
    bbl_run->expr_out = NEW_BV( num_defuses-1 );
    bvtmp = bbl_run->expr_out;
    bbl_run->expr_out = bv_diff( uset, bbl_run->expr_kill, num_defuses-1 );
    free( bvtmp );
    bbl_run = bbl_run->next;
  }

  /* Iteratively compute in and out set until they converge. */
  change = true;
  while ( change ) {
    printf( "Computing inout: iteration\n" );
    change = false;
    bbl_run = bhead;
    while( bbl_run != NULL ) {
      bbl_run->expr_in = compute_expr_in_bb( bbl_run );
      oldout = bbl_run->expr_out;
      bbl_run->expr_out = compute_expr_out_bb( bbl_run );
      if ( bv_unequal_check(oldout, bbl_run->expr_out, num_defuses-1) == true ) {
	change = true;
      }
      free( oldout );
      bbl_run = bbl_run->next;
    }
  }
  printf( "Converge!\n" );
}

/**
 * Carry out global available expression analysis.
 */
void avail_expr( TAC_seq *tacseq )
{
  bbl *bbl_run;

  //printf( "Number of local variables/tmps = %d\n", num_vars );
  //printf( "Number of defs/uses of local vars/tmps = %d\n", num_defuses );

  uset = NEW_BV( num_defuses-1 );
  /* For each local var/tmp compute the set of expressions that involve it. */
  compute_expr_bv( tacseq );
  print_bv( "Uset", uset, num_defuses-1 );

  /* For each block, compute its gen and kill set. */
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    bbl_run->expr_gen = NEW_BV( num_defuses-1 );
    bbl_run->expr_kill = NEW_BV( num_defuses-1 );
    compute_expr_gen_kill( bbl_run );
    bbl_run = bbl_run->next;
  }

  compute_expr_in_out();
}

