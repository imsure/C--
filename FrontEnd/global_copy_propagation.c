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

static bool debug = true; // debug switch for the module.

/**
 * Counter the number of defs of local var/tmp 'stptr' in the
 * set of reaching definition 'rf'.
 */
static int count_num_defs( bitvec *rf, symtabnode *stptr, TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  int def_counter = 0;

  while ( tac != NULL ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg
	 || tac->optype == Retrieve ) { // only look for instructions that define a variable.
      if ( TEST_BIT(rf, tac->id-1) ) { // see if 'tac' is in 'rf' set.
	if ( tac->dest->val.stptr == stptr ) {
	  ++def_counter; // update counter
	}
      }
    }
    tac = tac->next;
  }
  return def_counter;
}

/**
 * We carry out global copy propagation per basic block.
 */
static void global_copy_propagation_bb( bbl *bb, TAC_seq *tacseq )
{
  TAC *tac = bb->first_tac;
  bitvec *rf; // record set of reaching defs at each point in the 'bb'.
  int iternum = 0;
  int def_counter = 0; // used to hold the number of defs of a local var/tmp.

  rf = bb->in; // initialized with the set of defs that reaches to the entry of the block.
  while ( iternum < bb->numtacs ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ) { // def & use
      if ( is_valid_local(tac->operand1) ) {
	def_counter = count_num_defs( rf, tac->operand1->val.stptr, tacseq );
	if ( debug ) {
	  printf( "Number of def for %s reaches here is %d\n",
		  tac->operand1->val.stptr->name, def_counter );
	}
      }

      if ( is_valid_local(tac->operand2) ) {
	def_counter = count_num_defs( rf, tac->operand2->val.stptr, tacseq );
	if ( debug ) {
	  printf( "Number of def for %s reaches here is %d\n",
		  tac->operand2->val.stptr->name, def_counter );
	}
      }
    } else if ( tac->optype == Retrieve ) { // def only
    } else if ( tac->optype == Return ) { // use only
    }
    tac = tac->next;
    ++iternum;
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
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    global_copy_propagation_bb( bbl_run, tacseq );
    bbl_run = bbl_run->next;
  }
}
