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

/* A pool (bit vector) of registers available for coloring.
   ($11,$12,...,$25) */
#define REG_POOL 0x1FFFC00
#define K 15 // total number of available register for coloring

/* a list of local vars/tmps of the current processed function
   with their live ranges identified and each of them is a
   vertex of register interference graph. */
extern localvars *locals;

typedef struct Stack {
  symtabnode **vals;
  int top;
} Stack;

Stack stack;

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
 * Initialize stack for register allocation.
 */
static void init_stack()
{
  int size = 0;
  localvars *lvrun = locals->next;
  while ( lvrun != NULL ) {
    size++;
    lvrun = lvrun->next;
  }

  stack.vals = (symtabnode **) zalloc( size * sizeof(symtabnode *) );
  stack.top = -1; // no element at the beginning.
  printf( "size of stack: %d\n", size );
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
      /* Pick a vertex not yet removed and has degree < 'K' to remove. */
      if ( !(stptr->removed) && stptr->degree < K ) {
	printf( "%s(degree=%d) is picked to be removed.\n",
		stptr->name, stptr->degree );
	remove_vertex( stptr );
	stack.vals[ ++(stack.top) ] = stptr; // push removed vertex to stack.
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
 * Find and return a register number that does not
 * conflict any register numbers in 'used_regs'.
 */
static int find_a_color( bitvec used_regs )
{
  int i;
  printf( "conflicting registers: 0x%x\n", used_regs );
  /* Pick up a register from register pool that is not in 'used_regs'. */
  for ( i = 10; i < 25; ++i ) {
    if ( !TEST_BIT( &used_regs, i ) ) {
      return i+1;
    }
  }
  return -1; // should not reach here!
}

/**
 * Assign color to removed vertex 'stptr'.
 */
static void assign_color( symtabnode *stptr )
{
  colive_list *clrun = stptr->colives->next;
  /* A bit vector of registers allocated to the neighbors of 'stptr'. */
  bitvec used_regs = 0; // no need to be a pointer since we
                        // have only 15 registers available.
  
  stptr->removed = false; // add it back to graph
  /* Iterate through its neighbors. */
  while ( clrun != NULL ) {
    stptr->degree++;
    clrun->tmp_removed = false; // add edge back
    if ( !(clrun->stptr->removed) ) {
      /* need to choose a different color with 'clrun->stptr'. */
      SET_BIT( &used_regs, clrun->stptr->regnum - 1 );
    }
    clrun = clrun->next;
  }

  stptr->regnum = find_a_color( used_regs );
  printf( "Assigning register $%d to %s\n", stptr->regnum, stptr->name );
}

/**
 * Coloring the register interference graph formed by variable
 * in 'locals' with 'K' available registers in 'REG_POOL'.
 */
static void graph_coloring()
{
  symtabnode *stptr;
  int i;
  for ( i = stack.top; i >= 0; --i ) {
    /* Pop variable out of stack. */
    stptr = stack.vals[ i ];
    assign_color( stptr );
  }
}

static void print_stack()
{
  int i;
  printf( "stack top: %d\n", stack.top );
  for ( i = stack.top; i >= 0; --i ) {
    printf( "%s, ", stack.vals[i]->name );
  }
  putchar( '\n' );
}

void reg_alloc()
{
  init_stack();
  put_vertices2stack();
  graph_coloring();
}
