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
 * Check whether the given 'optype' is a relational operation.
 */
static bool is_relational( SyntaxNodeType optype )
{
  switch ( optype ) {
  case Equals:
  case Neq:
  case Leq:
  case Lt:
  case Geq:
  case Gt:
    return true;
  default:
    return false;
  }
}

void print_bbl()
{
  bbl *bbl_run = bhead;

  while( bbl_run != NULL ) {
    printf( "BBL%d(starts: %s, ends: %d, prev: BBL%d)\n",
	    bbl_run->bblnum, bbl_run->first_tac->dest->val.label,
	    bbl_run->last_tac->optype, (bbl_run->prev != NULL) ? bbl_run->prev->bblnum : -1 );
    bbl_run = bbl_run->next;
  }  
}

/**
 * Construct the list of basic block for the current function.
 *
 * The TAC generator guarantees that the leader (the first instruction)
 * for each block is always a compiler generated label except the first
 * basic block whose leader is a funtion label. This may introduce some
 * unnecessary labels, but makes it easier to construct basic blocks. 
 */
void construct_basic_block( TAC_seq *tacseq )
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
    if ( tac->optype == Goto || is_relational(tac->optype) == true ||
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

  print_bbl();
}

