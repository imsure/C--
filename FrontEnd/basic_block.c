/**
 * Implementation of basic block.
 * Effective when the comipler is invoked with -O1 option.
 * *******************************************************
 *
 * Author: Shuo Yang
 * Email: imsure95@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "protos.h"
#include "syntax-tree.h"
#include "basic_block.h"

label_list *lhead; // header to a list of compiler generated labels
bbl *bhead; // header to the basic block list of the current function.

/**
 * Collect all compiler generated labels into the linked
 * list 'lhead'.
 */
void collect_labels( TAC_seq *tacseq )
{
  TAC *tac = tacseq->start;
  label_list *llist_head, *llist_run;

  llist_head = (label_list *) zalloc( sizeof(label_list) );
  llist_run = llist_head;

  /* Collect all compiler generated label instructions. */
  while ( tac != NULL ) {
    if ( tac->optype == Label && tac->operand1 == NULL ) { // omit function labels
      llist_run->next_label = (label_list *) zalloc( sizeof(label_list) );
      llist_run->next_label->mylabel = tac;
      llist_run = llist_run->next_label;
    }
    tac = tac->next;
  }
  
  lhead = llist_head; // for the use of other modules
}

/**
 * Construct the list of basic block for the current function.
 *
 * The TAC generator guarantees that the leader (the first instruction)
 * for each block is always a compiler generated label except the first
 * basic block whose leader is a funtion label. This may introduce some
 * unnecessary labels, but makes it easier to construct basic blocks.
 */
static void construct_bb_list( TAC_seq *tacseq )
{
  TAC *tac;
  bbl *bbl_head, *bbl_run;
  int bbcounter = 0;

  bbl_head = (bbl *) zalloc( sizeof(bbl) );
  bbl_head->first_tac = tacseq->start; // start is always a function label
  bbl_head->bblnum = bbcounter++;
  bbl_run = bbl_head;

  tac = tacseq->start->next;
  while ( tac != NULL ) {
    if ( tac->optype == Goto || is_relational_op(tac->optype) == true ||
	 (tac->next != NULL)? tac->next->optype == Label : false ) { // identify the last tac.
      bbl_run->last_tac = tac; // fill in last tac for the current bbl
      /* Construct the next bbl. */
      bbl_run->next = (bbl *) zalloc( sizeof(bbl) );
      bbl_run->next->bblnum = bbcounter++;
      bbl_run->next->prev = bbl_run;
      if ( tac->next->optype == Label ) { // leader should always be a label.
	bbl_run->next->first_tac = tac->next;
      } else {
	fprintf( stderr, "Not a label (%d)! Sth wierd happended!\n", tac->next->optype );
	exit( -1 );
      }
      bbl_run = bbl_run->next;
      tac = tac->next->next; // two steps forward
      continue;
    }
    tac = tac->next;
  }
  
  if ( bbl_run->last_tac == NULL ) {
    /* Fill in last tac (should be a return statement) for the last bbl. */
    bbl_run->last_tac = tacseq->end;
  }

  bhead = bbl_head; // make it globally accessible.
}

/**
 * Lookup and return the basic block with the first TAC (leader)
 * be the label instruction 'succ_label'.
 */
static bbl *bbl_lookup( const char *succ_label )
{
  bbl *bbl_run;
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    if ( strcmp(bbl_run->first_tac->dest->val.label, succ_label) == 0 ) {
      return bbl_run;
    }
    bbl_run = bbl_run->next;
  }
  return NULL;
}

/**
 * Append bbl 'pred' to bbl 'bb's predecessor list.
 */
static void bbl_append_pred( bbl *bb, bbl *pred )
{
  control_flow_list *cfl;

  if ( bb->pred == NULL ) {
    bb->pred = (control_flow_list *) zalloc( sizeof(control_flow_list) );
    bb->pred->bb = pred;
  } else {
    cfl = bb->pred;
    while ( cfl->next != NULL ) {
      cfl = cfl->next;
    }
    cfl->next = (control_flow_list *) zalloc( sizeof(control_flow_list) );
    cfl->next->bb = pred;
  }
}

/**
 * Construct control flow information for basic blocks.
 */
static void construct_bb_control_flow()
{
  TAC *tac;
  bbl *bbl_run, *bbl_succ;
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    tac = bbl_run->last_tac;
    if ( tac->optype == Goto ) { // unconditional jump, one successor
      /* current basic block has only one successor. */
      bbl_run->succ = (control_flow_list *) zalloc( sizeof(control_flow_list) );
      bbl_succ = bbl_lookup( tac->dest->val.label );
      bbl_run->succ->bb = bbl_succ; // the basic block current block jumps to is the only successor
      bbl_append_pred( bbl_succ, bbl_run );
    } else if ( is_relational_op(tac->optype) == true ) { // conditional jump, two successors
      bbl_run->succ = (control_flow_list *) zalloc( sizeof(control_flow_list) );
      bbl_run->succ->bb = bbl_run->next; // next basic block is a successor
      bbl_append_pred( bbl_run->next, bbl_run );
      
      bbl_run->succ->next = (control_flow_list *) zalloc( sizeof(control_flow_list) );
      bbl_succ = bbl_lookup( tac->dest->val.label );
      bbl_run->succ->next->bb = bbl_succ; // the basic block current block jumps to is another successor
      bbl_append_pred( bbl_succ, bbl_run );
    } else if ( (tac->next != NULL)? tac->next->optype == Label : false ) {
      /* not a jump instruction, only one successor which is next basic block. */
      bbl_run->succ = (control_flow_list *) zalloc( sizeof(control_flow_list) );
      bbl_run->succ->bb = bbl_run->next;
      bbl_append_pred( bbl_run->next, bbl_run );
    }
    
    bbl_run = bbl_run->next;
  }
}

/**
 * Construct control flow information for basic blocks.
 */
static void count_tac_num()
{
  TAC *tac;
  bbl *bbl_run;
  int count;
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    count = 0;
    tac = bbl_run->first_tac;
    while ( tac != bbl_run->last_tac ) {
      ++count;
      tac = tac->next;
    }
    bbl_run->numtacs = ++count;
    bbl_run = bbl_run->next;
  }
}

/**
 * For degbugging purpose:
 *
 * print out all pairs of circular defined basic blocks.
 */
void print_circular_bbs()
{
  bbl *bbl_run = bhead;
  control_flow_list *succs, *preds;

  while( bbl_run != NULL ) {
    succs = bbl_run->succ;
    while ( succs != NULL ) {
      preds = bbl_run->pred;
      while ( preds != NULL ) {
	if ( succs->bb == preds->bb ) {
	  printf( "BBL%d and BBL%d have a circular definition!\n",
		  bbl_run->bblnum, succs->bb->bblnum );
	}
	preds = preds->next;
      }
      succs = succs->next;
    }
    bbl_run = bbl_run->next;
  }
}

/**
 * Check if basic block 'bb_from' and its successor 'bb_to'
 * form a circular referenece, that is, 'bb_to' is also a
 * predecessor of 'bb_from'.
 */
bool check_circular_bbs( bbl *bb_from, bbl *bb_to )
{
  control_flow_list *preds;

  preds = bb_from->pred;
  while ( preds != NULL ) {
    if ( bb_to == preds->bb ) {
      return true;
    }
    preds = preds->next;
  }
  return false;
}

void bb_reset_visit_counter()
{
  bbl *bbl_run = bhead;

  while( bbl_run != NULL ) {
    bbl_run->visit_counter = 0;
    bbl_run = bbl_run->next;
  }
}

void construct_basic_block( TAC_seq *tacseq )
{
  construct_bb_list( tacseq );
  count_tac_num();
  construct_bb_control_flow();
  //print_circular_bbs();
}
