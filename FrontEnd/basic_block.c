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

typedef struct basic_block_list {
  int bblnum;
  TAC *first_tac;
  TAC *last_tac;
  struct basic_block_list *pred, *succ;
  struct basic_block_list *prev, *next;
} bbl;

typedef struct Label_List label_list;
extern label_list *lhead;

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

/**
 *
 */
void construct_basic_block( TAC_seq *tacseq )
{
  TAC *tac;
  label_list *llist_run;
  bbl *bbl_head, *bbl_run;

  llist_run = lhead;

  bbl_head = (bbl *) zalloc( sizeof(bbl) );
  bbl_head->first_tac = tacseq->start; // start is always a function label
  bbl_run = bbl_head;

  tac = tacseq->start->next;
  /* Collect all compiler generated label instructions. */
  while ( tac != NULL ) {
    if ( tac->optype == Goto || is_relational(tac->optype) == true ) { // identify the last tac.
      bbl_run->last_tac = tac;
      /* start next bbl */
      bbl_run->next = (bbl *) zalloc( sizeof(bbl) );
      if ( tac->next->optype == Label ) {
	bbl_run->next->first_tac = tac->next;
      } else {
	fprintf( stderr, "Not a label (%d)! Sth wierd happend!\n", tac->next->optype );
	exit( -1 );
      }
      bbl_run = bbl_run->next;
      tac = tac->next->next; // two step forward
      continue;
    }
    tac = tac->next;
  }
  if ( bbl_run->last_tac == NULL ) {
    bbl_run->last_tac = tacseq->end;
  }

  bbl_run = bbl_head;
  while( bbl_run != NULL ) {
    printf( "BBL starts at label: %s\n", bbl_run->first_tac->dest->val.label );
    printf( "BBL ends at optype: %d\n", bbl_run->last_tac->optype );
    bbl_run = bbl_run->next;
  }
}

