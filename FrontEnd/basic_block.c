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

typedef struct Label_List label_list;
extern label_list *lhead; // header to a list of compiler generated labels

typedef struct basic_block_list {
  int bblnum;
  TAC *first_tac;
  TAC *last_tac;
  struct basic_block_list *pred, *succ;
  struct basic_block_list *prev, *next;
} bbl;

bbl *bhead; // header to the basic block list of the current function.

/**
 * A table containing copy pairs: lhs = rhs.
 * lhs_res could be: t_Int, t_Char, t_Tmp_Var or t_Tmp_Addr.
 * rhs_op could be: t_Int, t_Char, t_Tmp_Var. (we do not want
 * to propagation t_Tmp_Addr because referencing array elemnts
 * is expensive).
 * Example:
 * x = y;
 * _tvar0 = x;
 * *_taddr0 = _tvar0;
 */
typedef struct copytable {
  address *lhs_res, *rhs_op;
  struct copytable *next;
} copytable;

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

static bool is_arith_op( SyntaxNodeType optype )
{
  switch ( optype ) {
  case Plus:
  case BinaryMinus:
  case UnaryMinus:
  case Mult:
  case Div:
    return true;
  default:
    return false;
  }
}

/**
 * Return the replaced operand if 'operand' is found in the
 * copy table 'ct' as a LHS result (lhs_res).
 */
static address *replace( address *operand, copytable *ct_head )
{
  copytable *ct = ct_head->next;
  while ( ct != NULL ) {
    if ( strcmp(ct->lhs_res->val.stptr->name,
		operand->val.stptr->name) == 0 ) { // found a match!
      return ct->rhs_op; // replace
    }
    ct = ct->next;
  }
  return operand; // do not replace
}

/**
 * Remove all pairs containing 'res' from copy table 'ct'.
 * The type of 'res' must be AT_StRef.
 */
static void remove_pair( address *res, copytable *ct_head )
{
  copytable *ct = ct_head->next;
  copytable *ct_prev = ct_head;
  copytable *tmp;
  
  while ( ct != NULL ) {
    if ( ct->lhs_res->val.stptr == res->val.stptr ) {
      ct_prev->next = ct->next;
      tmp = ct;
      ct = ct->next;
      free( tmp ); // remove 
      continue;
    } else if ( ct->rhs_op->atype == AT_StRef ) {
      /* only compare 'res' with ct->rhs_op when rhs_op's type is a symbel table entry
	 because it could just a constant value. */
      if ( ct->rhs_op->val.stptr == res->val.stptr ) {
	ct_prev->next = ct->next;
	tmp = ct;
	ct = ct->next;
	free( tmp ); // remove
	continue;
      }
    }
    ct_prev = ct;
    ct = ct->next;
  }
}

/**
 * Insert pair (res, op) into copytable 'ct_head'.
 */
static void insert_pair( address *res, address *op, copytable *ct_head )
{
  copytable *ct = ct_head;
  while ( ct->next != NULL ) {
    ct = ct->next;
  }
  ct->next = (copytable *) zalloc( sizeof(copytable) );
  ct->next->lhs_res = res;
  ct->next->rhs_op = op;
}

static void free_copytable( copytable *ct_head )
{
  copytable *tmp;
  copytable *ct = ct_head;
  
  while ( ct != NULL ) {
    tmp = ct;
    ct = ct->next;
    free(tmp);
  }
}

/**
 * Performe copy propgation for the basic block 'bb'.
 */
static void copy_propagation_bb( bbl *bb )
{
  TAC *tac = bb->first_tac;
  copytable *ct_head = (copytable *) zalloc( sizeof(copytable) );

  while ( tac != bb->last_tac ) {
    if ( is_arith_op(tac->optype) == true ) { // arith: dest = op1 + op2
      if ( tac->operand1->atype != AT_Intcon &&
	   tac->operand1->atype != AT_Charcon ) { // only replace non-constant operand
	tac->operand1 = replace( tac->operand1, ct_head );
      }
      if ( tac->optype != UnaryMinus ) { // unary minus does not have operand2!
	if ( tac->operand2->atype != AT_Intcon &&
	     tac->operand2->atype != AT_Charcon ) { // only replace non-constant operand
	  tac->operand2 = replace( tac->operand2, ct_head );
	}
      }
      /* Remove all pairs in the copytable involves tac->dest (lhs).
	 since we are assigning a new value to it. */
      remove_pair( tac->dest, ct_head );
    } else if (tac->optype == Assg) { // a copy instruction: lhs = rhs
      if ( tac->operand1->atype != AT_Intcon &&
	   tac->operand1->atype != AT_Charcon ) { // only replace non-constant operand
	tac->operand1 = replace( tac->operand1, ct_head );
      }

      /* Remove all pairs in the copytable involves tac->dest (lhs).
	 since we are assigning a new value to it. */
      remove_pair( tac->dest, ct_head );

      /* Do not insert global variables due to potential side effect. */
      if ( tac->dest->val.stptr->scope != Global ) {
	if ( tac->operand1->atype != AT_StRef ||
	     tac->operand1->val.stptr->scope == Local ) {
	  insert_pair( tac->dest, tac->operand1, ct_head ); // update copy table
	}
      }
    } else if (tac->optype == Retrieve) {
      /* If we retrieve a value returned by a function into a variable,
	 we need to remove it from copy table. */
      if (tac->operand1 != NULL ) {
	remove_pair( tac->operand1, ct_head );
      }
    }
    tac = tac->next;
  }

  free_copytable( ct_head );
}

void copy_propagation()
{
  bbl *bbl_run, *tmp;
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    copy_propagation_bb( bbl_run );  
    bbl_run = bbl_run->next;
  }

  bbl_run = bhead;
  while( bbl_run != NULL ) {
    tmp = bbl_run;
    bbl_run = bbl_run->next;
    free( tmp );
  }
}

/**
 * Construct the list of basic block for the current function.
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

  bhead = bbl_head;  
}

