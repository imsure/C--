#ifndef BASIC_BLOCK_H
#define BASIC_BLOCK_H

#include "global.h"

/**
 * Linked list of compiler generated labels.
 */
typedef struct Label_List {
  TAC *mylabel;
  struct Label_List *next_label;
} label_list;

struct basic_block_list;

typedef struct bbl_control_flow_list {
  struct basic_block_list *bb;
  struct bbl_control_flow_list *next;
} control_flow_list;

/**
 * Represents basic block.
 */
typedef struct basic_block_list {
  int bblnum;
  TAC *first_tac;
  TAC *last_tac;
  control_flow_list *pred, *succ;
  struct basic_block_list *prev, *next;
  int numtacs; // number of TACs in side the basic block.
  /* For reaching definition. */
  bitvec *gen; // the set of definitions reaches the end of the basic block.
  bitvec *kill; // the set of definitions(in the entire funciton) that
                // are killed by definitions with in the basic block.
  bitvec *in;
  bitvec *out;

  /* For liveness analysis and dead code elimination. */
  bitvec *def;
  bitvec *use;
  bitvec *livein;
  bitvec *liveout;
  bitvec *used; // the set of local variables that are used inside the block.
} bbl;

#endif
