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

static void mips_entering_func( int stack_bytes )
{
  printf( "\tla $sp, -8($sp)\n" );
  printf( "\tsw $fp, 4($sp)\n" );
  printf( "\tsw $ra, 0($sp)\n" );
  printf( "\tla $fp, 0($sp)\n" );
  printf( "\tla $sp, -%d($sp)\n", stack_bytes );
}

static void mips_assg( instr *inst )
{
  symtabnode *dest_stptr = inst->dest->val.stptr;

  /* Check the type of LHS target. */
  
  /* Only operand1 is valid. put value of operand1 into $8. */
  switch (inst->operand1->atype) {
  case AT_Charcon:
  case AT_Intcon:
    printf( "\tli $8, %d\n", inst->operand1->val.iconst );
    break;
  case AT_StRef: // assigning a local/tmp variable
    printf( "\tlw $8, -%d($fp)\n", inst->operand1->val.stptr->fp_offset );
    break;
  }

  printf( "\tsw $8, -%d($fp)\n", dest_stptr->fp_offset );
}

static void mips_param( instr *inst )
{
  /* load parameter into register $8. TODO: check the type(array?) and scope! */
  printf( "\tlw $8, -%d($fp)\n", inst->operand1->val.stptr->fp_offset );
  printf( "\tla $sp, -4($sp)\n" );
  printf( "\tsw $8, 0($sp)\n" );
}

static void mips_call( instr *inst )
{
  printf( "\tjal %s\n", inst->operand1->val.stptr->name );
  printf( "\tla $sp, %d($sp)\n", inst->operand2->val.iconst * 4 );
}

static void mips_return( instr *inst )
{
  /* code for void func */
  printf( "\tla $sp, 0($fp)\n" );  
  printf( "\tlw $ra, 0($sp)\n" );
  printf( "\tlw $fp, 4($sp)\n" );
  printf( "\tla $sp, 8($sp)\n" );
  printf( "\tjr $ra\n" );
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
    case Assg: // mips code for assignement
      mips_assg( inst );
      break;
    case Return:
      mips_return( inst );
      break;
    case Param:
      mips_param( inst );
      break;
    case Call:
      mips_call( inst );
      break;
    default:
      return;
    }
    putchar( '\n' );
  }
}
