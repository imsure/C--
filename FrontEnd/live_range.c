#include "bitvector.h"
#include "protos.h"
#include "syntax-tree.h"
#include "basic_block.h"

extern bbl *bhead; // header to the basic block list of the current function.
extern int num_defuses; // total number of definitions inside the current processed function.

/**
 * Check if 'tac' is a valid definition of a local variable/tmp.
 */
static bool is_valid_local_def( TAC *tac )
{
  if ( is_arith_op(tac->optype) || tac->optype == Assg ||
       tac->optype == Retrieve ) {
    if ( is_valid_local( tac->dest ) ) {
      return true;
    }
  }
  return false;
}

/**
 * Check if 'tac' could potentially read a local variable.
 */
static bool is_valid_local_read( TAC *tac )
{
  if ( is_arith_op(tac->optype) || tac->optype == Assg ||
       tac->optype == Param || tac->optype == Return ||
       is_relational_op(tac->optype) ) {
    return true;
  }
  return false;
}

/**
 * Compute the live range within the basic block 'bb' for the
 * local variable defined in 'tac'. The result is stored in 'lr'.
 * 'tac_in_bb' is true if 'tac' belongs to 'bb', otherwise false.
 */
static void live_range_bb( bbl *bb, TAC *tac, live_range *lr,
			   bool tac_in_bb )
{
  TAC *tacrun;
  control_flow_list *cfl;
  bool keeprunning = true;

  if ( tac_in_bb == true ) tacrun = tac->next;
  else tacrun = bb->first_tac;

  /* Put all instructions that uses 'tac->dest' and can be reached
     by the definition of 'tac->dest' into its live range. */
  while ( keeprunning ) {
    if ( tacrun == bb->last_tac ) {
      keeprunning = false;
    }
    if ( is_valid_local_def( tacrun ) ) { // variable is redefined
      return;
    }
    if ( is_valid_local_read( tacrun ) ) {
      if ( is_valid_local( tacrun->operand1 ) &&
	   tacrun->operand1->val.stptr == tac->dest->val.stptr ) {
	SET_BIT( lr->val, tacrun->id-1 );
      }
      if ( is_valid_local( tacrun->operand2 ) &&
	   tacrun->operand2->val.stptr == tac->dest->val.stptr ) {
	SET_BIT( lr->val, tacrun->id-1 );
      }
    }
    tacrun = tacrun->next;
  }

  /* If the variable is alive at the exit of the block and the definition
     can reach to the exist of the block, recursively compute the live
     range for the variable by going down the control-flow-graph. */
  if ( TEST_BIT( bb->liveout, tac->dest->val.stptr->varid-1 ) &&
       TEST_BIT( bb->out, tac->id-1 ) ) {
    cfl = bb->succ;
    while ( cfl != NULL ) {
      live_range_bb( cfl->bb, tac, lr, false );
      cfl = cfl->next;
    }
  } else {
    return;
  }
}

/**
 * Compute live ranges for all local variables of the current
 * processed function.
 */
void compute_live_ranges()
{
  TAC *tac;
  int iternum;
  bbl *bbl_run = bhead;
  symtabnode *stptr;
  live_range *lr, *lrun;
  
  while( bbl_run != NULL ) {
    tac = bbl_run->first_tac;
    iternum = 0;
    while ( iternum < bbl_run->numtacs ) {
      if ( is_valid_local_def( tac ) ) {
	stptr = tac->dest->val.stptr;
	lr = (live_range *) zalloc( sizeof(live_range) );
	lr->val = NEW_BV( num_defuses-1 );
	live_range_bb( bbl_run, tac, lr, true );
	if ( stptr->live_ranges == NULL ) {
	  stptr->live_ranges = lr;
	} else { // append lr to the end of list
	  lrun = stptr->live_ranges;
	  while ( lrun->next != NULL ) {
	    lrun = lrun->next;
	  }
	  lrun->next = lr;
	}
      }
      tac = tac->next;
    }

    bbl_run = bbl_run->next;
  }
}
