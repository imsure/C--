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
 * Entry point for global copy propagation.
 *
 * Algorithm:
 * For each basic block:
 *     For each intruction that defines/uses a local variable/tmp:
 *     (Assg, arithmetic, Retrieve, Return)
 *         Compute set of reaching definitions just before the instruction;
 *         If the instruction is arithmetic or Return:
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
}
