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

/* Defined in basic_block.c */
extern label_list *lhead; // header to a list of compiler generated labels
extern bbl *bhead; // header to the basic block list of the current function.

/**
 * A set of live variables (only for local variables. int/char/t_Tmp_Var).
 */
typedef struct live_set {
  symtabnode *stptr;
  struct live_set *next;
} live_set;

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

/**
 * Perform copy propagation.
 * Transform:
 * t1 = z
 * u = t1 + 1
 *
 * into:
 * t1 = z
 * u = z + 1
 *
 * This is done for further dead code elimination since
 * copy propagation could produce many unused copy instructions
 * which can be eliminated.
 */
void copy_propagation()
{
  bbl *bbl_run;
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    copy_propagation_bb( bbl_run );  
    bbl_run = bbl_run->next;
  }

  /* bbl_run = bhead; */
  /* while( bbl_run != NULL ) { */
  /*   tmp = bbl_run; */
  /*   bbl_run = bbl_run->next; */
  /*   free( tmp ); */
  /* } */
}

static void insert_ls( live_set *ls_head, address *var )
{
  live_set *ls = ls_head;
  while ( ls->next != NULL ) {
    if ( var->val.stptr == ls->next->stptr ) {
      /* var already exists in the set. */
      return;
    }
    ls = ls->next;
  }
  ls->next = (live_set *) zalloc( sizeof(live_set) );
  ls->next->stptr = var->val.stptr;
}

static bool is_in_liveset( address *var, live_set *ls_head )
{
  live_set *ls = ls_head;
  while ( ls->next != NULL ) {
    if ( var->val.stptr == ls->next->stptr ) {
      /* var already exists in the set. */
      return true;
    }
    ls = ls->next;
  }
  return false;
}

static void remove_from_liveset( address *var, live_set *ls_head )
{
  live_set *ls = ls_head->next;
  live_set *ls_prev = ls_head;
  live_set *tmp;
  
  while ( ls != NULL ) {
    if ( ls->stptr == var->val.stptr ) {
      ls_prev->next = ls->next;
      tmp = ls;
      ls = ls->next;
      free( tmp ); // remove 
      continue;
    }
    ls_prev = ls;
    ls = ls->next;
  }
}

static void eliminate_dead_code( bbl *bb )
{
  TAC *tac = bb->first_tac;
  TAC *tac_prev, *tac_tmp;
  live_set *ls_head = (live_set *) zalloc( sizeof(live_set) );

  /* Fill live set with all local variables and t_Tmp_Var tmps. */
  while ( tac != bb->last_tac ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ) {
      if ( is_valid_local(tac->dest) ) {
	insert_ls( ls_head, tac->dest );
      }
      if ( is_valid_local(tac->operand1) ) {
	insert_ls( ls_head, tac->operand1 );
      }
      if ( is_valid_local(tac->operand2) ) {
	insert_ls( ls_head, tac->operand2 );
      }
    }
    tac = tac->next;
  }
  /* Last tac could be an copy instruction to!!! */
  if ( is_arith_op(tac->optype) || tac->optype == Assg ) {
    if ( is_valid_local(tac->dest) ) {
      insert_ls( ls_head, tac->dest );
    }
    if ( is_valid_local(tac->operand1) ) {
      insert_ls( ls_head, tac->operand1 );
    }
    if ( is_valid_local(tac->operand2) ) {
      insert_ls( ls_head, tac->operand2 );
    }
  }

  tac = bb->last_tac;
  /* Traverse backwards. */
  while ( tac != bb->first_tac ) {
    if ( is_arith_op(tac->optype) || tac->optype == Assg ) {
      if ( is_valid_local(tac->dest) == true ) { // write dest, dead
	if ( is_in_liveset(tac->dest, ls_head) == true ) {
	  /* tac->dest is dead at this point. */
	  remove_from_liveset( tac->dest, ls_head );
	} else { // tac can be delete
	  tac_prev = tac->prev;
	  tac_prev->next = tac->next;
	  tac->next->prev = tac_prev;
	  tac_tmp = tac;
	  tac = tac_prev;
	  continue;
	}
      }
      if ( is_valid_local(tac->operand1) ) { // read operand1, live
	if ( is_in_liveset(tac->operand1, ls_head) == false ) {
	  /* tac->dest is alive at this point. */
	  insert_ls( ls_head, tac->operand1 );
	}
      }
      if ( is_valid_local(tac->operand2) ) { // read operand2, live
	if ( is_in_liveset(tac->operand2, ls_head) == false ) {
	  /* tac->dest is alive at this point. */
	  insert_ls( ls_head, tac->operand2 );
	}
      }
    }
    if ( tac->optype == Param ) { // read to operand1
      if ( is_valid_local(tac->operand1) ) { // read operand1, alive
	if ( is_in_liveset(tac->operand1, ls_head) == false ) {
	  /* tac->dest is alive at this point. */
	  insert_ls( ls_head, tac->operand1 );
	}
      }
    }

    tac = tac->prev;
  }
}

/**
 * Perform liveness analysis on basic blocks.
 */
void liveness_local()
{
  bbl *bbl_run;
  
  bbl_run = bhead;
  while( bbl_run != NULL ) {
    eliminate_dead_code( bbl_run );
    bbl_run = bbl_run->next;
  }
}

