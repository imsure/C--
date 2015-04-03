/**
 * A short and concise description goes here.
 * *************************************************
 *
 * Author: Shuo Yang
 * Email: imsure95@gmail.com
 */

#include "bitvector.h"
#include "protos.h"
#include "syntax-tree.h"
#include "basic_block.h"

/* A pool of registers available for coloring.
   ($11,$12,...,$25) */
#define REG_POOL 0x1FFFC00
#define K 15 // total number of available register for coloring

/* a list of local vars/tmps of the current processed function
   with their live ranges identified and each of them is a
   vertex of register interference graph. */
extern localvars *locals;

static void remove_edge( symtabnode *stptr_from,
			 symtabnode *stptr_to )
{
  colive_list *clrun = stptr_from->colives->next;
  while ( clrun != NULL ) {
    if ( clrun->stptr == stptr_to ) {
      clrun->tmp_removed = true;
      printf( "Removing edge: %s --> %s\n",
	      stptr_from->name, stptr_to->name );
      return;
    }
    clrun = clrun->next;
  }
}

/**
 * Remove vertex 'stptr' from 'locals' temporarily.
 */
static void remove_vertex( symtabnode *stptr )
{
  colive_list *clrun = stptr->colives->next;
  stptr->removed = true; // indicate it is removed temporarily.
  printf( "Removing vertex %s\n", stptr->name );
  while ( clrun != NULL ) {
    if ( !(clrun->stptr->removed) ) { // ignore those have been removed
      /* Indicate edge 'stptr' --> 'clrun->stptr' is
	 temporarily removed.*/
      clrun->tmp_removed = true;
      stptr->degree--; // update degree
      clrun->stptr->degree--; // update degree
      printf( "Removing edge: %s --> %s\n",
	      stptr->name, clrun->stptr->name );
      
      /* Also 'clrun->stptr' also needs to know this edge is removed
	 since we are duplicating the same edge on both ends.*/
      remove_edge( clrun->stptr, stptr );
    }
    clrun = clrun->next;
  }
}

/**
 * Check whether the graph is empty or not.
 */
static bool is_graph_empty()
{
  localvars *lvrun = locals->next;
  while ( lvrun != NULL ) {
    if ( !(lvrun->stptr->removed) ) {
      return false; // not empty
    }
    lvrun = lvrun->next;
  }
  return true;
}

/**
 * Put vertices with 'K' fewer neighbors onto stack.
 */
static void put_vertices2stack()
{
  symtabnode *stptr;
  localvars *lvrun;

  while ( !is_graph_empty() ) { // repeat until the graph is empty.
    lvrun = locals->next;
    while ( lvrun != NULL ) {
      stptr = lvrun->stptr;
      if ( !(stptr->removed) && stptr->degree < K ) {
	printf( "%s(degree=%d) is picked to be removed.\n",
		stptr->name, stptr->degree );
	remove_vertex( stptr );
      }
      lvrun = lvrun->next;
    }
  }
  printf( "Done! graph is empty now.\n" );
  lvrun = locals->next;
  while ( lvrun != NULL ) {
    printf( "%s(degree=%d)\n", lvrun->stptr->name, lvrun->stptr->degree );
    lvrun = lvrun->next;
  }
}

/**
 * Coloring the register interference graph formed by variable
 * in 'locals' with 'K' available registers in 'REG_POOL'.
 */
static void graph_coloring()
{
}

void reg_alloc()
{
  put_vertices2stack();
  graph_coloring();
}
