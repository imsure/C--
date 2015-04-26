/**
 * Global Copy Progation.
 * (across basic blocks, but is intra-procedural)
 * ******************************************************
 *
 * Author: Shuo Yang
 * Email: imsure95@gmail.com
 */

#include "bitvector.h"
#include "protos.h"
#include "syntax-tree.h"
#include "basic_block.h"

/**
 * For debug purpose.
 */
extern void printtac( TAC *tac );
extern void print_bv( const char *name, bitvec *bv, int len );
extern void copy_propagation();

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

static bool debug = false; // debug switch for the module.
//static bool debug = true; // debug switch for the module.

/**
 * Counter the number of defs of local var/tmp 'stptr' in the
 * set of reaching definition 'rf'.
 * 'tmptac' is used for holding the address of tac that defines 'stptr'.
 */
static int count_num_defs( bitvec *rf, symtabnode *stptr, TAC_seq *tacseq, TAC **tmptac )
{
  TAC *tac = tacseq->start;
  int def_counter = 0;

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg
	 || tac->optype == Retrieve ) { // only look for instructions that define a variable.
      if ( TEST_BIT(rf, tac->id-1) ) { // see if 'tac' is in 'rf' set.
	if ( tac->dest->val.stptr == stptr ) {
	  tac->num_uses += 1; // increment num_uses counter to indicate it is used once.
	  ++def_counter; // update counter
	  *tmptac = tac;
	}
      }
    }
    tac = tac->next;
  }
  return def_counter;
}

/**
 * Kill the defs in the set of reaching definition 'rf' that define 'stptr'.
 */
static void kill_defs( bitvec *rf, symtabnode *stptr, TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg
	 || tac->optype == Retrieve ) { // only look for instructions that define a variable.
      if ( TEST_BIT(rf, tac->id-1) ) { // see if 'tac' is in 'rf' set.
	if ( tac->dest->val.stptr == stptr ) {
	  CLEAR_BIT( rf, tac->id-1 );
	}
      }
    }
    tac = tac->next;
  }
}

/**
 * Peform copy propagation on a local var/tmp
 * given the set of reaching definition 'rf', 'operand' on which we
 * try to propagate and tac sequence.
 */
static void copy_propagation_on_operand( bitvec *rf,
					 address **operand_target,
					 TAC_seq *tacseq, bbl *bb, TAC *curr_tac )
{
  TAC *tmptac;
  int def_counter = 0; // used to hold the number of defs of a local var/tmp.
  address *operand = *operand_target;

  if ( is_valid_local(operand) ) {
    def_counter = count_num_defs( rf, operand->val.stptr, tacseq, &tmptac );
    if ( debug ) {
      printf( "Number of def for %s reaches here is %d\n",
	      operand->val.stptr->name, def_counter );
    }
    
    if ( def_counter == 0 ) { return; }
    if ( def_counter > 1 ) {
      /* Multiple definitions of 'operand' reaches current use of 'operand'.
	 Cannot do copy propagation on 'operand'. */
      return;
    }
    if ( def_counter == 1 ) {
      if ( debug ) {
	printf( "The only TAC that defines %s: ", operand->val.stptr->name );
	printtac( tmptac );
	putchar( '\n' );
      }
      if ( tmptac->optype == Assg ) { // copy instruction
	if ( tmptac->operand1->atype == AT_Intcon ||
	     tmptac->operand1->atype == AT_Charcon ) {
	  /* Constant can be safely propagated. */
	  tmptac->num_uses--; // decrement num_uses counter.
	  if ( debug ) {
	    printf( "Propagating constant %d\n", tmptac->operand1->val.iconst );
	  }
	  *operand_target = tmptac->operand1;
	} else if ( is_valid_local(tmptac->operand1) ) {
	  /* First check if any definition of tmptac->operand1 reaches here. */
	}
      }
    }
  }
}

/**
 * We carry out global copy propagation per basic block.
 */
static void global_copy_propagation_bb( bbl *bb, TAC_seq *tacseq )
{
  TAC *tac = bb->first_tac;
  bitvec *rf; // record set of reaching defs at each point in the 'bb'.
  int iternum = 0;
  TAC *tmptac;

  if ( debug ) {
    printf( "Start processing block %s\n", bb->first_tac->dest->val.label );
  }

  rf = NEW_BV( num_defuses-1 );
  rf = bv_union( rf, bb->in, num_defuses-1 ); // initialized with the set of defs that reaches to the entry of the block.

  /* if ( strcmp(bb->first_tac->dest->val.label, "_L11") == 0 ) { */
  /*   print_bv( "Initial RF", rf, num_defuses-1 ); */
  /* } */

  while ( iternum < bb->numtacs ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ) { // def & use
      copy_propagation_on_operand( rf, &(tac->operand1), tacseq, bb, tac );
      copy_propagation_on_operand( rf, &(tac->operand2), tacseq, bb, tac );

      if ( tac->optype == UnaryMinus && (tac->operand1->atype == AT_Intcon ||
					 tac->operand1->atype == AT_Charcon) ) {
	if ( debug ) {
	  printf( "CP turned a unary minus into a constant assignment!\n" );
	}
	tac->optype = Assg;
	tac->operand1->val.iconst = -tac->operand1->val.iconst; // reverse the constant value.
      }

      /* Update reaching definition set 'rf'. */
      if ( is_valid_local(tac->dest) ) {
	/* tac->dest kills all defs in 'rf' that define tac->dest. */
	kill_defs( rf, tac->dest->val.stptr, tacseq );
	SET_BIT( rf, tac->id-1 ); // add current tac into 'rf' set.
      }
    } else if ( is_relational_op(tac->optype) ) { // use only
      copy_propagation_on_operand( rf, &(tac->operand1), tacseq, bb, tac );
      copy_propagation_on_operand( rf, &(tac->operand2), tacseq, bb, tac );
    } else if ( tac->optype == Retrieve ) { // def only
      /* Update reaching definition set 'rf'. */
      if ( is_valid_local(tac->dest) ) {
	/* tac->dest kills all defs in 'rf' that define tac->dest. */
	kill_defs( rf, tac->dest->val.stptr, tacseq );
	SET_BIT( rf, tac->id-1 ); // add current tac into 'rf' set.
      }      
    } else if ( tac->optype == Return || tac->optype == Param ) { // use only
      /* Do not do copy propgation here, but need to update 'num_uses' counter. */
      if ( is_valid_local(tac->operand1) ) {
	count_num_defs( rf, tac->operand1->val.stptr, tacseq, &tmptac );
      }
    }
    tac = tac->next;
    ++iternum;
  }

  if ( debug ) {
    printf( "End of processing block %s\n", bb->first_tac->dest->val.label );
  }
}

/**
 * Delete unused definitions generated by copy propagation.
 * A definition is dead if its 'num_uses' is 0.
 */
static void delete_unused_defs( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  TAC *tac_prev, *tac_tmp;

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg
	 || tac->optype == Retrieve ) { // only look for instructions that define a variable.
      if ( is_valid_local(tac->dest) && tac->num_uses == 0 ) { // unused, dead
	if ( debug ) {
	  printf( "TAC" );
	  printtac( tac );
	  printf( "is dead!!!\n" );
	}

	/* Delete 'tac'. */
	tac_prev = tac->prev;
	tac_prev->next = tac->next;
	tac->next->prev = tac_prev;
	tac_tmp = tac;
	free( tac_tmp );
	tac = tac_prev->next;;
	continue;
      }
    }
    tac = tac->next;
  }
}

/**
 * Entry point for global copy propagation.
p *
 * Algorithm:
 * For each basic block:
 *     For each intruction that defines/uses a local variable/tmp:
 *     (Assg, arithmetic, Retrieve, Return)
 *         Compute set of reaching definitions just before the instruction;
 *         If the instruction is arithmetic or Assg or Return:
 *             For each local var/tmp 'x' used on the RHS:
 *                 Check the set of reaching definitions that reaches to this point:
 *                 case-1: no definition of 'x' reaches to this point, just continue;
 *                 case-2: there are defs of 'x' reaches here:(increment 'num_uses' of each by 1)
 *                     case-2.1: there are more than 1 defs of 'x' reach here, cannot
 *                               do copy propagtion. But for each def of 'x', need to
 *			         increment its 'num_uses'(initially 0) by 1 since it is being used.
 *                     case-2.2: there is only 1 def of 'x' reaches here.
 *                         case-2.2.1: if this def of 'x' is not a copy instruction(Assg),
 *                                     just increment its 'num_uses' by 1 and continue;
 *                         case-2.2.2: if this def of 'x' is a copy instruction(Assg)
 *                             case-2.2.2.1: if its RHS is a constant:
 *                                           do copy propagation & decrement 'num_uses' by 1.
 *                             case-2.2.2.2: if its RHS is not a constant, but a local var/tmp 'y':
 *                                           check if any defs of 'y' reaches at this point, if yes,
 *                                           just increment 'num_uses' by 1 and continue;
 *                                           if no, do copy propagation & decrement 'num_uses' by 1.
 */
void global_copy_propagation( TAC_seq *tacseq )
{
  bbl *bbl_run;

  //  printf( "Number of local variables/tmps = %d\n", num_vars );
  //  printf( "Number of defs/uses of local vars/tmps = %d\n", num_defuses );

  bbl_run = bhead;
  while( bbl_run != NULL ) {
    global_copy_propagation_bb( bbl_run, tacseq );
    bbl_run = bbl_run->next;
  }

  /* Delete dead code generated by copy propagation. */
  delete_unused_defs( tacseq );
}
