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
  
  /* Only operand1 is valid. put value of operand1 into $8. */
  switch (inst->operand1->atype) {
  case AT_Charcon:
  case AT_Intcon:
    printf( "\tli $8, %d\n", inst->operand1->val.iconst );
    break;
  case AT_StRef: // assigning a local/tmp variable
    printf( "\tlw $8, -%d($fp)\n", inst->operand1->val.stptr->fp_offset );
    if ( inst->operand1->val.stptr->is_addr ) {
      printf( "\tlw $9, ($8)\n" );
      printf( "\tsw $9, -%d($fp)\n", dest_stptr->fp_offset );
      return;
    }
    break;
  }

  /* Check the type of LHS target. global/local/array? */
  switch ( dest_stptr->type ) {
  case t_Char:
    printf( "\tsb $8, -%d($fp)\n", dest_stptr->fp_offset );
    break;
  case t_Int:
    printf( "\tsw $8, -%d($fp)\n", dest_stptr->fp_offset );
    break;
  case t_Tmp:
    if ( dest_stptr->is_addr ) { // array address
      printf( "\tlw $9, -%d($fp)\n", dest_stptr->fp_offset );
      printf( "\tsw $8, ($9)\n" );
    } else {
      printf( "\tsw $8, -%d($fp)\n", dest_stptr->fp_offset );
    }
    break;
  }
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

static void mips_binop( instr *inst )
{
  /* TODO: add support for globals. */

  if ( inst->operand1->val.stptr->type == t_Array ) {
    printf( "\tla $8, -%d($fp)\n", inst->operand1->val.stptr->fp_offset );
  } else {
    printf( "\tlw $8, -%d($fp)\n", inst->operand1->val.stptr->fp_offset );
  }

  if ( inst->operand2->atype != AT_Intcon ) {
    printf( "\tlw $9, -%d($fp)\n", inst->operand2->val.stptr->fp_offset );
  } else {
    printf( "\tli $9, %d\n", inst->operand2->val.iconst );
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

  printf( "\tsw $10, -%d($fp)\n", inst->dest->val.stptr->fp_offset );
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
