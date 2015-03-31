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

int num_vars; // total number of variables inside the current
              // processed function. This will be the size of bit vectors.
extern bbl *bhead; // header to the basic block list of the current function.

/**
 * Check if address 'var' is a valid local variable, either
 * user defined or compiler generated tmp variables. The name
 * of local array variable is excluded.
 */
static bool valid_local( address *var )
{
  if ( var != NULL && var->atype == AT_StRef &&
       var->val.stptr->scope == Local &&
       var->val.stptr->type != t_Array ) {
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
 * Check if 'tac' is a special instruction for calculating
 * the address of an array element, like: _taddr0 = x + 4
 * where x is the name of array.
 */
static bool array_addr_cal_tac( TAC *tac)
{
  if ( is_arith_op(tac->optype) &&
       tac->dest->val.stptr->type == t_Tmp_Addr &&
       tac->operand1->atype == AT_StRef &&
       tac->operand1->val.stptr->type == t_Array ) {
    return true;
  }
  return false;
}
     
/**
 * Compute def and use set for the basic block 'bb'
 * using its local information.
 */
static void compute_defuse_bb( bbl *bb )
{
  TAC *tac = bb->last_tac;
  int iternum = 0;

  while ( iternum < bb->numtacs ) {
    if ( array_addr_cal_tac(tac) == true ) {
      if ( valid_local(tac->operand2) == true ) {
	CLEAR_BIT( bb->def, tac->operand2->val.stptr->varid-1 );
	SET_BIT( bb->use, tac->operand2->val.stptr->varid-1 );
	//SET_BIT( bb->used, tac->operand2->val.stptr->varid-1 );
      }
      tac = tac->prev;
      iternum++;
      continue;
    }
    if ( is_arith_op(tac->optype) || tac->optype == Assg ) {
      if ( tac->dest->val.stptr->scope == Local ) {
	if ( TEST_BIT(bb->def, tac->dest->val.stptr->varid-1) ) {
	  /* if tac->dest is already in the def set, the current definition
	     must be dead. for example:
	     x = x + 1;
	     x = 5;
	     x = x + 1 is dead before it is overwritten by x = 5.
	     in this case, mark the current tac as dead, then
	     continue to the next iteration. */
	  /* printf( "Dead code (local):" ); */
	  /* printtac( tac ); */
	  /* printf( "\n" ); */
	  tac->is_dead = true;
	  tac = tac->prev;
	  iternum++;
	  continue;
	} else {
	  SET_BIT( bb->def, tac->dest->val.stptr->varid-1 );
	  CLEAR_BIT( bb->use, tac->dest->val.stptr->varid-1 );
	}
      }
      if ( valid_local(tac->operand1) == true ) {
	CLEAR_BIT( bb->def, tac->operand1->val.stptr->varid-1 );
	SET_BIT( bb->use, tac->operand1->val.stptr->varid-1 );
	//SET_BIT( bb->used, tac->operand1->val.stptr->varid-1 );
      }
      if ( valid_local(tac->operand2) == true ) {
	CLEAR_BIT( bb->def, tac->operand2->val.stptr->varid-1 );
	SET_BIT( bb->use, tac->operand2->val.stptr->varid-1 );
	//SET_BIT( bb->used, tac->operand2->val.stptr->varid-1 );
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
	//SET_BIT( bb->used, tac->dest->val.stptr->varid-1 );
      }
    } else if ( is_relational_op(tac->optype) ) {
      if ( valid_local(tac->operand1) == true ) {
	CLEAR_BIT( bb->def, tac->operand1->val.stptr->varid-1 );
	SET_BIT( bb->use, tac->operand1->val.stptr->varid-1 );
	//SET_BIT( bb->used, tac->operand1->val.stptr->varid-1 );
      }      

      if ( valid_local(tac->operand2) == true ) {
	CLEAR_BIT( bb->def, tac->operand2->val.stptr->varid-1 );
	SET_BIT( bb->use, tac->operand2->val.stptr->varid-1 );
	//SET_BIT( bb->used, tac->operand2->val.stptr->varid-1 );
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
 * Compute the out set for the basic block 'bb'.
 * bb.liveout = union of in sets of all successors of bb.
 */
static bitvec *compute_outset_bb( bbl *bb )
{
  bitvec *bvtmp;
  bitvec *res = NEW_BV( num_vars-1 );
  control_flow_list *cfl = bb->succ;
  
  while ( cfl != NULL ) {
    bvtmp = res;
    res = bv_union( res, cfl->bb->livein, num_vars-1 );
    free( bvtmp );
    cfl = cfl->next;
  }
  return res;
}

/**
 * Compute the in set for the basic block 'bb'.
 * bb.livein = bb.use union (bb.liveout - bb.def)
 */
static bitvec *compute_inset_bb( bbl *bb )
{
  bitvec *bvtmp;
  bitvec *res;
  
  res = bv_diff( bb->liveout, bb->def, num_vars-1 );
  bvtmp = res;
  res = bv_union( res, bb->use, num_vars-1 );
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
  bitvec *bvtmp, *oldin;
  bool change;

  /* Initialize in and out set for each basic block. */
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    bbl_run->livein = NEW_BV( num_vars-1 );
    bbl_run->liveout = NEW_BV( num_vars-1 );
    bvtmp = bbl_run->livein;
    bbl_run->livein = bv_union( bbl_run->livein, bbl_run->use, num_vars-1 );
    free( bvtmp );
    bbl_run = bbl_run->next;
  }

  /* Iteratively compute in and out set until they converge. */
  change = true;
  while ( change ) {
    change = false;
    bbl_run = bhead;
    while( bbl_run != NULL ) {
      bbl_run->liveout = compute_outset_bb( bbl_run );
      oldin = bbl_run->livein;
      bbl_run->livein = compute_inset_bb( bbl_run );
      if ( bv_unequal_check(oldin, bbl_run->livein, num_vars-1) == true ) {
	change = true;
      }
      free( oldin );
      bbl_run = bbl_run->next;
    }
  }
}

static void detect_dead_code_bb( bbl *bb )
{
  TAC *tac = bb->last_tac;
  int iternum = 0;

  while ( iternum < bb->numtacs ) {
    if ( array_addr_cal_tac(tac) == true ) {
      if ( valid_local(tac->operand2) == true ) {
	SET_BIT( bb->used, tac->operand2->val.stptr->varid-1 );
      }
      tac = tac->prev;
      iternum++;
      continue;
    }
    if ( tac->is_dead == true ) {
      tac = tac->prev;
      iternum++;
      continue;
    }
    if ( is_arith_op(tac->optype) || tac->optype == Assg ) {
      if ( tac->dest->val.stptr->scope == Local ) {
	if ( bv_test_bit(bb->liveout, tac->dest->val.stptr->varid-1) == false &&
	     bv_test_bit(bb->used, tac->dest->val.stptr->varid-1) == false ) {
	  /* if tac->dest is neither in bb->out nor in bb->used,
	     then tac must be dead. */
	  /* printf( "Dead code (global):" ); */
	  /* printtac( tac ); */
	  /* printf( "\n" ); */
	  tac->is_dead = true;
	  tac = tac->prev;
	  iternum++;
	  continue;
	} else { // update bb->used set only if tac is not dead
	  if ( valid_local(tac->operand1) == true ) {
	    SET_BIT( bb->used, tac->operand1->val.stptr->varid-1 );
	  }
	  if ( valid_local(tac->operand2) == true ) {
	    SET_BIT( bb->used, tac->operand2->val.stptr->varid-1 );
	  }
	}
      }
    } else if ( tac->optype == Retrieve ) { // def
      if ( tac->dest->val.stptr->scope == Local ) {
	if ( !TEST_BIT(bb->liveout, tac->dest->val.stptr->varid-1) &&
	     !TEST_BIT(bb->used, tac->dest->val.stptr->varid-1) ) {
	  /* if tac->dest is neither in bb->out nor in bb->used,
	     then tac must be dead. */
	  /* printf( "Dead code (global):" ); */
	  /* printtac( tac ); */
	  /* printf( "\n" ); */
	  tac->is_dead = true;
	  tac = tac->prev;
	  iternum++;
	  continue;
	}
      }
    } else if ( tac->optype == Param ) { // use
      if ( tac->dest->val.stptr->scope == Local ) {
	SET_BIT( bb->used, tac->dest->val.stptr->varid-1 );
      }
    } else if ( is_relational_op(tac->optype) ) {
      if ( valid_local(tac->operand1) == true ) {
	SET_BIT( bb->used, tac->operand1->val.stptr->varid-1 );
      }
      if ( valid_local(tac->operand2) == true ) {
	SET_BIT( bb->used, tac->operand2->val.stptr->varid-1 );
      }      
    }
    tac = tac->prev;
    iternum++;
  }
}

static void detect_dead_code()
{
  bbl *bbl_run;
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    bbl_run->used = NEW_BV( num_vars-1 );
    detect_dead_code_bb( bbl_run );
    bbl_run = bbl_run->next;
  }
}

static void remove_dead_code( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  TAC *tmp;

  while ( tac != NULL ) {
    if ( tac->is_dead == true ) {
      tac->prev->next = tac->next;
      tac->next->prev = tac->prev;
      tmp = tac;
      printf( "Remove: " );
      printtac( tac );
      putchar( '\n' );
      tac = tac->next;
      free( tmp );
      continue;
    }
    tac = tac->next;
  }
}

void liveness_global( TAC_seq *tacseq )
{
  num_vars = count_assign_varids( tacseq );
  compute_defuse();
  compute_inout();
  detect_dead_code();
  remove_dead_code( tacseq );
}
