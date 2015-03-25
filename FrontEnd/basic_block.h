#ifndef BASIC_BLOCK_H
#define BASIC_BLOCK_H

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
} bbl;

#endif
