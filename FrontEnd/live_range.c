#include "bitvector.h"
#include "protos.h"
#include "syntax-tree.h"
#include "basic_block.h"

extern bbl *bhead; // header to the basic block list of the current function.
extern int num_defuses; // total number of definitions inside the current processed function.

extern void printtac( TAC *tac );

/* a list of local vars/tmps of the current processed function
   with their live ranges identified. */
localvars *locals; 

/**
 * Check if 'tac' is a valid definition of a local variable/tmp.
 */
static bool is_valid_local_def( TAC *tac )
{
  if ( is_arith_op(tac->optype) || tac->optype == Assg ||
       tac->optype == Retrieve ) {
    if ( is_valid_local( tac->dest ) ) {
      return true;
    }
  }
  return false;
}

/**
 * Check if 'tac' could potentially read a local variable.
 */
static bool is_valid_local_read( TAC *tac )
{
  if ( is_arith_op(tac->optype) || tac->optype == Assg ||
       tac->optype == Param || tac->optype == Return ||
       is_relational_op(tac->optype) ) {
    return true;
  }
  return false;
}

/**
 * Compute the live range within the basic block 'bb' for the
 * local variable defined in 'tac'. The result is stored in 'lr'.
 * 'tac_in_bb' is true if 'tac' belongs to 'bb', otherwise false.
 */
static void live_range_bb( bbl *bb, TAC *tac, live_range *lr,
			   bool tac_in_bb )
{
  TAC *tacrun;
  control_flow_list *cfl;
  bool keeprunning = true;

  if ( tac_in_bb == true ) {
    if ( tac == bb->last_tac ) {
      goto check;
    }
    tacrun = tac->next;
  }
  else {
    tacrun = bb->first_tac;
  }

  /* Put all instructions that uses 'tac->dest' and can be reached
     by the definition of 'tac->dest' into its live range. */
  while ( keeprunning ) {
    if ( tacrun == bb->last_tac ) {
      keeprunning = false;
    }
    if ( is_valid_local_def( tacrun ) &&
	 tac->dest->val.stptr == tacrun->dest->val.stptr ) { // variable is redefined
      return;
    }
    if ( is_valid_local_read( tacrun ) ) {
      if ( is_valid_local( tacrun->operand1 ) &&
	   tacrun->operand1->val.stptr == tac->dest->val.stptr ) {
	SET_BIT( lr->val, tacrun->id-1 );
	//printf( "add tac %d as used tac for %s\n", tacrun->id, tac->dest->val.stptr->name );
      }
      if ( is_valid_local( tacrun->operand2 ) &&
	   tacrun->operand2->val.stptr == tac->dest->val.stptr ) {
	SET_BIT( lr->val, tacrun->id-1 );
	//printf( "add tac %d as used tac for %s\n", tacrun->id, tac->dest->val.stptr->name );
      }
    }
    tacrun = tacrun->next;
  }

 check:
  /* If the variable is alive at the exit of the block and the definition
     can reach to the exist of the block, recursively compute the live
     range for the variable by going down the control-flow-graph. */
  if ( TEST_BIT( bb->liveout, tac->dest->val.stptr->varid-1 ) &&
       TEST_BIT( bb->out, tac->id-1 ) ) {
    if ( bb->visit_counter >= 2 ) {
      return;
    }
    bb->visit_counter++;
    cfl = bb->succ;
    while ( cfl != NULL ) {
      live_range_bb( cfl->bb, tac, lr, false );
      cfl = cfl->next;
    }
  } else {
    return;
  }
}

void print_live_range()
{
  symtabnode *stptr;
  live_range *lrun;
  localvars *lvtmp = locals->next;

  while ( lvtmp != NULL ) {
    stptr = lvtmp->stptr;
    lrun = stptr->live_ranges;
    printf( "Live range for %s\n", stptr->name );
    if ( stptr->type != t_Tmp_Var ) {
      print_bv( "", stptr->single_lr, num_defuses-1 );
    } else {
      while ( lrun != NULL ) {
	print_bv( "", lrun->val, num_defuses-1 );
	lrun = lrun->next;
      }
    }
    lvtmp = lvtmp->next;
  }
}

/**
 * Merge overlapped live ranges.
 *
 * To keep it simple:
 * 1. Do not touch compiler-generated tmp variables;
 * 2. Only merge disjoint live ranges for user-defined local
 *    variables into a single live range. (without checking
 *    whether or not they overlap.)
 */
void merge_live_range()
{
  symtabnode *stptr;
  live_range *lrun;
  localvars *lvtmp = locals->next;
  bitvec *bv, *bvtmp;

  while ( lvtmp != NULL ) {
    stptr = lvtmp->stptr;
    if ( stptr->type != t_Tmp_Var ) {
      bv = NEW_BV( num_defuses-1 );
      lrun = stptr->live_ranges;
      while ( lrun != NULL ) {
	bvtmp = bv;
	bv = bv_union( bv, lrun->val, num_defuses-1 );
	free( bvtmp );
	lrun = lrun->next;
      }
      stptr->single_lr = bv;
    }
    lvtmp = lvtmp->next;
  }
}

static void add_edge( symtabnode *stptr_from, symtabnode *stptr_to )
{
  colive_list *clrun;

  //  printf( "adding edge between %s and %s\n", stptr_from->name, stptr_to->name );

  /* stptr_from --> stptr_to */
  clrun = stptr_from->colives;
  while ( clrun->next != NULL ) {
    clrun = clrun->next;
  }
  clrun->next = (colive_list *) zalloc( sizeof(colive_list) );
  clrun->next->stptr = stptr_to;

  //  printf( "%s ==> %s\n", stptr_from->name, stptr_to->name );

  /* stptr_to --> stptr_from */
  clrun = stptr_to->colives;
  while ( clrun->next != NULL ) {
    clrun = clrun->next;
  }
  clrun->next = (colive_list *) zalloc( sizeof(colive_list) );
  clrun->next->stptr = stptr_from;

  //  printf( "%s ==> %s\n", stptr_to->name, stptr_from->name );
}

static void identify_edge_tmp2tmp( symtabnode *stptr_from,
				   symtabnode *stptr_to )
{
  live_range *lrun_from, *lrun_to;
  
  lrun_from = stptr_from->live_ranges;
  lrun_to = stptr_to->live_ranges;

  while ( lrun_from != NULL ) {
    while ( lrun_to != NULL ) {
      if ( bv_have_overlap( lrun_from->val, lrun_to->val, num_defuses-1 ) ) {
	/* add an edge 'stptr_from' -> 'stptr_to' */
	add_edge( stptr_from, stptr_to );
	//printf( "%s and %s overlap\n", stptr_from->name, stptr_to->name );
	return;
      }
      lrun_to = lrun_to->next;
    }
    lrun_from = lrun_from->next;
  }  
}

static void identify_edge_tmp2var( symtabnode *stptr_from,
				   symtabnode *stptr_to )
{
  live_range *lrun_from;
  bitvec *lv_to;
  
  lrun_from = stptr_from->live_ranges;
  lv_to = stptr_to->single_lr;

  while ( lrun_from != NULL ) {
    if ( bv_have_overlap( lrun_from->val, lv_to, num_defuses-1 ) ) {
      /* add an edge 'stptr_from' -> 'stptr_to' */
      add_edge( stptr_from, stptr_to );
      //printf( "%s and %s overlap\n", stptr_from->name, stptr_to->name );
      return;
    }
    lrun_from = lrun_from->next;
  }  
}

static void identify_edge_var2var( symtabnode *stptr_from,
				   symtabnode *stptr_to )
{
  bitvec *lv_from, *lv_to;
  
  lv_from = stptr_from->single_lr;
  lv_to = stptr_to->single_lr;

  if ( bv_have_overlap( lv_from, lv_to, num_defuses-1 ) ) {
    /* add an edge 'stptr_from' -> 'stptr->to' */
    add_edge( stptr_from, stptr_to );
    //printf( "%s and %s overlap\n", stptr_from->name, stptr_to->name );
  }
}

static void identify_edge_var2tmp( symtabnode *stptr_from,
				   symtabnode *stptr_to )
{
  bitvec *lv_from;
  live_range *lrun_to;
  
  lv_from = stptr_from->single_lr;
  lrun_to = stptr_to->live_ranges;

  while ( lrun_to != NULL ) {
    if ( bv_have_overlap( lv_from, lrun_to->val, num_defuses-1 ) ) {
      /* add an edge 'stptr_from' -> 'stptr->to' */
      add_edge( stptr_from, stptr_to );
      //printf( "%s and %s overlap\n", stptr_from->name, stptr_to->name );
      return;
    }
    lrun_to = lrun_to->next;
  }
}

/**
 * identify the edges between 'stptr' and a list of varibles
 * pointed by 'lvrun'.
 */
static void identify_edges( symtabnode *stptr, localvars *lvrun )
{ 
  if ( lvrun == NULL ) {
    return;
  }

  if ( stptr->type == t_Tmp_Var ) {
    /* tmps have disjoint live ranges. */
    while ( lvrun != NULL ) {
      if ( lvrun->stptr->type == t_Tmp_Var ) {
	identify_edge_tmp2tmp( stptr, lvrun->stptr );
      } else {
	identify_edge_tmp2var( stptr, lvrun->stptr );
      }
      lvrun = lvrun->next;
    }
  } else {
    /* user-defined variables have a single live range. */
    while ( lvrun != NULL ) {
      if ( lvrun->stptr->type == t_Tmp_Var ) {
	identify_edge_var2tmp( stptr, lvrun->stptr );
      } else {
	identify_edge_var2var( stptr, lvrun->stptr );
      }
      lvrun = lvrun->next;
    }    
  }
}

void construct_interference_graph()
{
  symtabnode *stptr;
  localvars *lvrun1, *lvrun2;

  lvrun1 = locals->next;
  while ( lvrun1 != NULL ) {
    stptr = lvrun1->stptr;
    stptr->colives = (colive_list *) zalloc( sizeof(colive_list) );
    lvrun1 = lvrun1->next;
  }

  lvrun1 = locals->next;
  while ( lvrun1 != NULL ) {
    stptr = lvrun1->stptr;
    lvrun2 = lvrun1->next;
    identify_edges( stptr, lvrun2 );
    lvrun1 = lvrun1->next;
  }
}

void assign_degrees()
{
  symtabnode *stptr;
  localvars *lvrun;
  colive_list *clrun;

  lvrun = locals->next;
  while ( lvrun != NULL ) {
    stptr = lvrun->stptr;
    clrun = stptr->colives->next;
    while ( clrun != NULL ) {
      stptr->degree++;
      clrun = clrun->next;
    }
    //printf( "Degree of %s is: %d\n", stptr->name, stptr->degree );
    lvrun = lvrun->next;
  }
}

void print_graph()
{
  symtabnode *stptr;
  localvars *lvrun;
  colive_list *clrun;

  lvrun = locals->next;
  while ( lvrun != NULL ) {
    stptr = lvrun->stptr;
    printf( "%s(degree=%d):\n", stptr->name, stptr->degree );
    putchar( '\t' );
    clrun = stptr->colives->next;
    while ( clrun != NULL ) {
      printf( "%s, ", clrun->stptr->name );
      clrun = clrun->next;
    }
    putchar( '\n' );
    lvrun = lvrun->next;
  }
}

/**
 * Compute live ranges for all local variables of the current
 * processed function.
 */
void compute_live_ranges()
{
  TAC *tac;
  int iternum;
  bbl *bbl_run = bhead;
  symtabnode *stptr;
  live_range *lr, *lrun;
  localvars *lvtmp;

  locals = (localvars *) zalloc( sizeof(localvars) );
  
  while( bbl_run != NULL ) {
    tac = bbl_run->first_tac;
    iternum = 0;
    while ( iternum < bbl_run->numtacs ) {
      if ( is_valid_local_def( tac ) ) {
	/* Compute live range for 'tac->dest'. */
	stptr = tac->dest->val.stptr;
	lr = (live_range *) zalloc( sizeof(live_range) );
	lr->val = NEW_BV( num_defuses-1 );
	bb_reset_visit_counter();
	live_range_bb( bbl_run, tac, lr, true );
	SET_BIT( lr->val, tac->id-1 ); // live range also contains the definition itself
	if ( stptr->live_ranges == NULL ) { // found a new variable
	  lvtmp = locals;
	  while ( lvtmp->next != NULL ) {
	    lvtmp = lvtmp->next;
	  }
	  lvtmp->next = (localvars *) zalloc( sizeof(localvars) );
	  lvtmp->next->stptr = stptr;
	  stptr->live_ranges = lr;
	} else { // append lr to the end of list
	  lrun = stptr->live_ranges;
	  while ( lrun->next != NULL ) {
	    lrun = lrun->next;
	  }
	  lrun->next = lr;
	}
      }
      iternum++;
      tac = tac->next;
    }

    bbl_run = bbl_run->next;
  }
  merge_live_range();
  //  print_live_range();
  construct_interference_graph();
  assign_degrees();
  //  print_graph();
}
