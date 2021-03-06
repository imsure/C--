/**
 * A short and concise description goes here.
 * *************************************************
 *
 * Author: Shuo Yang
 * Email: imsure95@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "syntax-tree.h"

void mips_print_int()
{
  printf( "\t.text\n" );
  printf( "print_int:\n" );

  printf( "\tli $v0, 1\n" );  
  printf( "\tlw $a0, 0($sp)\n" );
  printf( "\tsyscall\n" );

  printf( "\tjr $ra\n\n" );
}

void mips_print_string()
{
  printf( "\t.text\n" );
  printf( "print_string:\n" );

  printf( "\tli $v0, 4\n" );  
  printf( "\tlw $a0, 0($sp)\n" );
  printf( "\tsyscall\n" );

  printf( "\tjr $ra\n\n" );
}

/* MIPS code for entering a function routine.
   'stack_frame_size': size of locals/tmps in bytes. */
static void mips_entering_func( int stack_frame_size )
{
  printf( "\tla $sp, -8($sp) # allocate space for old $fp and $ra\n" );
  printf( "\tsw $fp, 4($sp) # save old $fp on stack\n" );
  printf( "\tsw $ra, 0($sp) # save old $ra on stack\n" );
  printf( "\tla $fp, 0($sp) # set up frame pointer\n" );
  printf( "\tla $sp, -%d($sp) # allocate stack frame for locals/tmps\n",
	  stack_frame_size );
}

static void load_constant( int val )
{
  if ( val < MAX_16bits ) { // valie is less than 16 bits wide
    printf( "\tli $8, %d # load constant < 16-bits\n", val );
  } else { // greater than 16 bits wide
    printf( "\tlui $8, %d # load higher 16-bits\n", val >> 16 );
    printf( "\tori $8, %d # load lower 16-bits\n", val & 0xffff );
  }
}

/* MIPS code for assignment: LHS = RHS. */
static void mips_assg( instr *inst )
{
  int val;
  symtabnode *lhs_stptr = inst->dest->val.stptr; // LHS must be a symbol table entry.
  symtabnode *rhs_stptr;
  bool is_rhs_array = false, is_int_array = false;

  /* Only operand1 is valid (RHS). put value of operand1 into $8. */
  switch (inst->operand1->atype) {
  case AT_Charcon: 
  case AT_Intcon:
    /* Loading constant */
    val = inst->operand1->val.iconst;
    load_constant( val );
    break;
  case AT_Stringcon:   /* a special case when we are passing a string constant to a function. */
    printf( "\tla $8, %s # load string const addr\n", inst->operand1->val.stptr->name );
    printf( "\tsw $8, -%d($fp) # store string const address\n", lhs_stptr->fp_offset );
    return;
  case AT_StRef: // assigning a global/local/tmp/strcon variable
    rhs_stptr = inst->operand1->val.stptr;
    if ( rhs_stptr->scope != Global ) { // todo: make rhs value always in $8
      if ( !rhs_stptr->formal ) { // local/tmp
	printf( "\tlw $8, -%d($fp) # load local/tmp\n", rhs_stptr->fp_offset );
	/* The value of the rhs might be an address for array assignment like:
	   x = A[5]; or A[i] = B[j]. */
	if ( rhs_stptr->is_addr ) { // in this case, this is true.
	  if ( rhs_stptr->elt_type == t_Int ) { // int array
	    printf( "\tlw $9, ($8) # load value of int array element\n" );
	    is_int_array = true;
	  } else { // char array
	    printf( "\tlb $9, ($8) # load value of char array element\n" );
	  }
	  is_rhs_array = true;
	}
      } else { // formal
	printf( "\tlw $8, %d($fp) # load formal argument/tmp\n",
		4*rhs_stptr->index + 4 );
      }
    } else { // lhs is a global variable
      switch( rhs_stptr->type ) {
      case t_Int:
	printf( "\tlw $8, %s # load global int %s\n", rhs_stptr->name );
	break;
      case t_Char:
	printf( "\tlb $8, %s # load global char %s\n", rhs_stptr->name );
	break;
      case t_Array:
	/* TODO: implement */
	break;
      }
    }
    break;
  }

  if ( lhs_stptr->scope == Local ) {
    if ( lhs_stptr->formal ) { // assign to formals
      printf( "\tsw $8, %d($fp) # load formal argument/tmp\n",
	      4*lhs_stptr->index + 4 );
      return;
    }
    if ( is_rhs_array ) { // RHS is an array ref, value is in $9
      switch ( lhs_stptr->type ) {
      case t_Char:
	printf( "\tsb $9, -%d($fp) # store value of array element into char\n",
		lhs_stptr->fp_offset );
	break;
      case t_Int:
	printf( "\tsw $9, -%d($fp) # store value of array element into int\n",
		lhs_stptr->fp_offset );
	break;
      case t_Tmp:
	if ( lhs_stptr->is_addr ) { // array address
	  printf( "\tlw $10, -%d($fp) # load array address\n", lhs_stptr->fp_offset );
	  if ( lhs_stptr->elt_type == t_Int ) {
	    printf( "\tsw $9, ($10) # store array element into int array\n" );
	  } else {
	    printf( "\tsb $9, ($10) # store array element into char array\n" );
	  }
	} else {
	  printf( "\tsw $9, -%d($fp)\n", lhs_stptr->fp_offset );
	}
	break;
      }      
    } else { // rhs is not an ref to array element, value is in $8
      switch ( lhs_stptr->type ) {
      case t_Char:
	printf( "\tsb $8, -%d($fp)\n", lhs_stptr->fp_offset );
	break;
      case t_Int:
	printf( "\tsw $8, -%d($fp)\n", lhs_stptr->fp_offset );
	break;
      case t_Tmp:
	if ( lhs_stptr->is_addr ) { // array address
	  printf( "\tlw $9, -%d($fp)\n", lhs_stptr->fp_offset );
	  if ( lhs_stptr->elt_type == t_Int ) {
	    printf( "\tsw $8, ($9) # store value into int array\n" );
	  } else {
	    printf( "\tsb $8, ($9) # store value into char array\n" );
	  }
	} else {
	  printf( "\tsw $8, -%d($fp)\n", lhs_stptr->fp_offset );
	}
	break;
      }
    }
  } else { // LHS is a global
    switch (lhs_stptr->type) {
    case t_Int:
      printf( "\tsw $8, %s # store value to global variable %s\n",
	      lhs_stptr->name, lhs_stptr->name );
      break;
    case t_Char:
      printf( "\tsb $8, %s # store value to global variable %s\n",
	      lhs_stptr->name, lhs_stptr->name );
      break;
    }
  }
}

static void mips_param( instr *inst )
{
  symtabnode *stptr = inst->operand1->val.stptr;

  if ( stptr->scope == Global ) { // global variable
    printf( "\tlw $8 %s # pusing global variable as param\n", stptr->name );
    printf( "\tla $sp, -4($sp) # allocate stack space for it\n" );
    printf( "\tsw $8, 0($sp) # push the parameter value onto stack\n" );
    return;
  }

  if ( stptr->formal ) {
    if ( stptr->type != t_Array ) {
      printf( "\tlw $8 %d($fp)\n", 4 * stptr->index + 4 );
    }
  } else {
  /* load parameter into register $8. TODO: check the type(array?) and scope! */
    if ( stptr->type == t_Array ) { // passing array
      printf( "\tla $8 -%d($fp) # passing array\n", stptr->fp_offset );
    } else {
      if ( stptr->is_addr ) {
	printf( "\tlw $9, -%d($fp) # load address of parameter\n", stptr->fp_offset );
	if ( stptr->elt_type == t_Int ) {
	  printf( "\tlw $8, ($9) # load value of int\n" );
	} else { // char array
	  printf( "\tlb $8, ($9) # load value of char\n" );
	}
      } else {
	printf( "\tlw $8, -%d($fp) # load parameter\n", stptr->fp_offset );
      }
    }
  }
  printf( "\tla $sp, -4($sp) # allocate stack space for it\n" );
  printf( "\tsw $8, 0($sp) # push the parameter value onto stack\n" );
}

static void mips_call( instr *inst )
{
  printf( "\tjal %s\n", inst->operand1->val.stptr->name );
  printf( "\tla $sp, %d($sp)\n", inst->operand2->val.iconst * 4 );
}

static void mips_return( instr *inst )
{
  if ( inst->operand1 != NULL ) { // non void function
    /* load return value into $8 */
    /* formal parameters */
    if ( inst->operand1->val.stptr->formal ) { // result in $8
      printf( "\tlw $v0, %d($fp) # load value of (formal) %s\n",
	      4 * inst->operand1->val.stptr->index + 4,
	      inst->operand1->val.stptr->name );
    } else { // local/tmp, result in $8
      if ( inst->operand1->val.stptr->is_addr ) {
	printf( "\tlw $8, -%d($fp) # load array address\n", inst->operand1->val.stptr->fp_offset );
	printf( "\tlw $9, ($8) # load array element from address\n" );
	printf( "\tli $10, 0\n" );
	printf( "\tadd $v0, $9, $10\n" );
      } else {
	printf( "\tlw $v0, -%d($fp) # load %s\n", inst->operand1->val.stptr->fp_offset,
		inst->operand1->val.stptr->name);
      }
    }
  }

  printf( "\tla $sp, 0($fp)\n" );  
  printf( "\tlw $ra, 0($sp)\n" );
  printf( "\tlw $fp, 4($sp)\n" );
  printf( "\tla $sp, 8($sp)\n" );
  printf( "\tjr $ra\n" );
}

static void mips_retrieve( instr *inst )
{
  if ( inst->operand1 != NULL ) { // non void function
    /* store return value from $v0 */
    if ( inst->operand1->val.stptr->formal ) {     /* formal parameters */
      printf( "\tsw $v0, %d($fp) # store return value to (formal) %s\n",
	      4 * inst->operand1->val.stptr->index + 4,
	      inst->operand1->val.stptr->name );
    } else { // local/tmp
      if ( inst->operand1->val.stptr->is_addr ) {
	printf( "\tlw $8, -%d($fp) # load array address\n", inst->operand1->val.stptr->fp_offset );
	printf( "\tsw $v0, ($8) # store %s\n", inst->operand1->val.stptr->name );
      } else {
	printf( "\tsw $v0, -%d($fp) # store %s\n", inst->operand1->val.stptr->fp_offset,
		inst->operand1->val.stptr->name);
      }
    }
  }
}

static void mips_binop( instr *inst )
{
  /* TODO: add support for globals. */
  if ( inst->operand1->val.stptr->scope == Global ) { // lhs is a global
    switch ( inst->operand1->val.stptr->type ) {
    case t_Int:
      printf( "\tlw $8, %s # load global int %s\n",
	      inst->operand1->val.stptr->name, inst->operand1->val.stptr->name );
      break;
    case t_Char:
      printf( "\tlb $8, %s # load global char %s\n",
	      inst->operand1->val.stptr->name, inst->operand1->val.stptr->name );
      break;
    case t_Array:
      printf( "\tla $8, %s # load global array address %s\n",
	      inst->operand1->val.stptr->name, inst->operand1->val.stptr->name );
      break;
    }
  } else { // scope: local

    /* formal parameters */
    if ( inst->operand1->val.stptr->formal ) { // result in $8
      if ( inst->operand1->val.stptr->type == t_Array ) {
	printf( "\tlw $8, %d($fp) # load address of array(formal) %s\n",
		4 * inst->operand1->val.stptr->index + 4,
		inst->operand1->val.stptr->name );
      } else {
	printf( "\tlw $8, %d($fp) # load value of (formal) %s\n",
		4 * inst->operand1->val.stptr->index + 4,
		inst->operand1->val.stptr->name );
      }
    } else { // local/tmp, result in $8
      if ( inst->operand1->val.stptr->type == t_Array ) {
	printf( "\tla $8, -%d($fp) # load address of array %s\n",
		inst->operand1->val.stptr->fp_offset, inst->operand1->val.stptr->name );
      } else if ( inst->operand1->val.stptr->is_addr ) {
	printf( "\tlw $8, -%d($fp) # load array address\n", inst->operand1->val.stptr->fp_offset );
	if ( inst->operand1->val.stptr->elt_type == t_Int ) { // int array element
	  printf( "\tlw $9, ($8) # load array element from address\n" );
	} else { // char array element
	  printf( "\tlb $9, ($8) # load array element from address\n" );
	}
	printf( "\tli $10, 0\n" );
	printf( "\tadd $8, $9, $10\n" );
      } else {
	printf( "\tlw $8, -%d($fp) # load %s\n", inst->operand1->val.stptr->fp_offset,
		inst->operand1->val.stptr->name);
      }
    }
  }

  if ( inst->operand2->atype != AT_Intcon &&
       inst->operand2->val.stptr->scope == Global ) { // lhs is a global
    switch ( inst->operand2->val.stptr->type ) {
    case t_Int:
      printf( "\tlw $9, %s # load global int %s\n",
	      inst->operand2->val.stptr->name, inst->operand2->val.stptr->name );
      break;
    case t_Char:
      printf( "\tlb $9, %s # load global char %s\n",
	      inst->operand2->val.stptr->name, inst->operand2->val.stptr->name );
      break;
    case t_Array:
      printf( "\tla $9, %s # load global array address %s\n",
	      inst->operand2->val.stptr->name, inst->operand2->val.stptr->name );
      break;
    }
  } else { // scope: local
    if ( inst->operand2->atype != AT_Intcon ) {
      if ( inst->operand2->val.stptr->formal ) { // result in $9
	printf( "\tlw $9, %d($fp) # load value of (formal) %s\n",
		4 * inst->operand2->val.stptr->index + 4,
		inst->operand2->val.stptr->name );
      } else {
	if ( inst->operand2->val.stptr->is_addr ) {
	  printf( "\tlw $9, -%d($fp) # load array address\n", inst->operand2->val.stptr->fp_offset );
	  if ( inst->operand2->val.stptr->elt_type == t_Int ) { // int array element
	    printf( "\tlw $10, ($9) # load array element from address\n" );
	  } else {
	    printf( "\tlb $10, ($9) # load array element from address\n" );
	  }
	  printf( "\tli $11, 0\n" );
	  printf( "\tadd $9, $10, $11\n" );
	} else {
	  printf( "\tlw $9, -%d($fp)\n", inst->operand2->val.stptr->fp_offset );
	}
      }
    } else {
      printf( "\tli $9, %d\n", inst->operand2->val.iconst );
    }
  }

  switch( inst->op ) {
    case Plus:
      printf( "\tadd $10, $8, $9\n" );
      break;
    case BinaryMinus:
      printf( "\tsub $10, $8, $9\n" );
      break;
    case Mult:
      printf( "\tmul $10, $8, $9\n" );
      break;
    case Div:
      printf( "\tdiv $10, $8, $9\n" );
      break;
  }

  if ( inst->dest->val.stptr->scope == Local ) {
    printf( "\tsw $10, -%d($fp)\n", inst->dest->val.stptr->fp_offset );
  } else {
    printf( "\tsw $10, %s # save value to global %s\n",
	    inst->dest->val.stptr->name, inst->dest->val.stptr->name );
  }
}

static void mips_unary( instr *inst )
{
  /* TODO: add support for globals. */

  /* formal parameters */
  if ( inst->operand1->val.stptr->formal ) { // result in $8
    if ( inst->operand1->val.stptr->type == t_Array ) {
      printf( "\tlw $8, %d($fp) # load address of array(formal) %s\n",
	      4 * inst->operand1->val.stptr->index + 4,
	      inst->operand1->val.stptr->name );
    } else {
      printf( "\tlw $8, %d($fp) # load value of (formal) %s\n",
	      4 * inst->operand1->val.stptr->index + 4,
	      inst->operand1->val.stptr->name );
    }
  } else { // local/tmp, result in $8
    if ( inst->operand1->val.stptr->type == t_Array ) {
      printf( "\tla $8, -%d($fp) # load address of array %s\n",
	      inst->operand1->val.stptr->fp_offset, inst->operand1->val.stptr->name );
    } else if ( inst->operand1->val.stptr->is_addr ) {
      printf( "\tlw $8, -%d($fp) # load array address\n", inst->operand1->val.stptr->fp_offset );
      printf( "\tlw $9, ($8) # load array element from address\n" );
      printf( "\tli $10, 0\n" );
      printf( "\tadd $8, $9, $10\n" );
    } else {
      printf( "\tlw $8, -%d($fp) # load %s\n", inst->operand1->val.stptr->fp_offset,
	      inst->operand1->val.stptr->name);
    }
  }

  printf( "\tneg $9, $8\n" );

  /* Todo: add support for formals and globals */
  printf( "\tsw $9, -%d($fp)\n", inst->dest->val.stptr->fp_offset );
}


static void mips_bincond( instr *inst )
{
  symtabnode *op1, *op2;
  if ( inst->operand1->atype == AT_Intcon ||
       inst->operand1->atype == AT_Charcon ) {
    printf( "\tli $8, %d\n", inst->operand1->val.iconst );
  } else {
    if ( inst->operand1->val.stptr->formal ) { // formals
      printf( "\tlw $8, %d($fp)\n", 4 * inst->operand1->val.stptr->index + 4 );
    } else {
      printf( "\tlw $8, -%d($fp)\n", inst->operand1->val.stptr->fp_offset );
    }
  }

  if ( inst->operand2->atype == AT_Intcon ||
       inst->operand2->atype == AT_Charcon ) {
    printf( "\tli $9, %d\n", inst->operand2->val.iconst );
  } else {
    if ( inst->operand2->val.stptr->formal ) { // formals
      printf( "\tlw $9, %d($fp)\n", 4 * inst->operand2->val.stptr->index +4 );
    } else {
      printf( "\tlw $9, -%d($fp)\n", inst->operand2->val.stptr->fp_offset );
    }
  }

  switch (inst->op) {
    case Equals:
      printf( "\tbeq $8, $9, %s\n", inst->dest->val.goto_label->dest->val.label );
      break;
    case Neq:
      printf( "\tbne $8, $9, %s\n", inst->dest->val.goto_label->dest->val.label );
      break;
    case Leq:
      printf( "\tble $8, $9, %s\n", inst->dest->val.goto_label->dest->val.label );
      break;
    case Lt:
      printf( "\tblt $8, $9, %s\n", inst->dest->val.goto_label->dest->val.label );
      break;
    case Geq:
      printf( "\tbge $8, $9, %s\n", inst->dest->val.goto_label->dest->val.label );
      break;
    case Gt:
      printf( "\tbgt $8, $9, %s\n", inst->dest->val.goto_label->dest->val.label );
      break;
  }
}

void tac2mips( tnode *t, int num_bytes_on_stack )
{
  instr *inst;

  for (inst = t->code->start; inst != NULL; inst = inst->next) {
    if ( inst->is_empty ) {
      continue;
    }
    switch ( inst->op ) {
    case Label:
      printf( "\t.text\n" );
      printf( "%s:", inst->dest->val.label );
      break;
    case Enter: // mips code for entering a function
      mips_entering_func( num_bytes_on_stack );
      break;
    case Plus:
    case BinaryMinus:
    case Mult:
    case Div:
      mips_binop( inst );
      break;
    case UnaryMinus:
      mips_unary( inst );
      break;
    case Assg: // mips code for assignement
      mips_assg( inst );
      break;
    case Equals:
    case Neq:
    case Leq:
    case Lt:
    case Geq:
    case Gt:
      mips_bincond( inst );
      break;
    case Return:
      mips_return( inst );
      break;
    case Retrieve:
      mips_retrieve( inst );
      break;
    case Param:
      mips_param( inst );
      break;
    case Call:
      mips_call( inst );
      break;
    case Goto:
      printf( "\tj %s\n", inst->dest->val.goto_label->dest->val.label );
      break;
    case Leave:
      printf( "\t# Ignore Leave operation for now.\n" );
    default:
      return;
    }
    putchar( '\n' );
  }
}
