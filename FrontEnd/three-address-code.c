/**
 * Routines for generating 3-address-code from syntax tree.
 * ********************************************************
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

#define LABEL "L"

int label_counter = 0; // counter for the labels.
int tmp_counter = 0; // counter for the temp variables.

three_addr_code *code_gen( tnode *t );

instr *newinstr( SyntaxNodeType op, address *operand1, address *operand2,
		 address *dest, bool is_empty )
{
  instr *quad = (instr *) zalloc( sizeof(instr) );
  quad->op = op;
  quad->dest = dest;
  quad->operand1 = operand1;
  quad->operand2 = operand2;
  quad->is_empty = is_empty;
  quad->next = NULL;

  return quad;
}

instr *newlabel()
{
  instr *quad = (instr *) zalloc( sizeof(instr) );
  quad->op = Label;
  quad->dest = (address *) zalloc( sizeof(address) );
  quad->dest->atype = AT_Label;
  sprintf( quad->dest->val.label, "%s%d", LABEL, label_counter++ );
  quad->operand1 = NULL;
  quad->operand2 = NULL;
  quad->is_empty = false;
  quad->next = NULL;

  return quad;
}

static void print_operands( instr *inst, char *op )
{
  if ( inst->operand1 != NULL ) {
    switch (inst->operand1->atype) {
    case AT_Intcon:
      printf( "%d ", inst->operand1->val.iconst );
      break;
    case AT_StRef:
      printf( "%s ", inst->operand1->val.stptr->name );
      break;
    }
  }

  printf( "%s ", op );

  if ( inst->operand2 != NULL ) {
    switch (inst->operand2->atype) {
    case AT_Intcon:
      printf( "%d ", inst->operand2->val.iconst );
      break;
    case AT_StRef:
      printf( "%s", inst->operand2->val.stptr->name );
      break;
    }
  }
}

void print_code( tnode *t )
{
  instr *inst;
  instr *end = t->code->end;

  for (inst = t->code->start; inst != NULL; inst = inst->next) {
    if ( inst->is_empty ) {
      continue;
    }
    switch ( inst->op ) {
    case Plus:
      printf( "%s = ", inst->dest->val.stptr->name ); 
      print_operands( inst, "+" );
      break;
    case BinaryMinus:
      printf( "%s = ", inst->dest->val.stptr->name ); 
      print_operands( inst, "-" );
      break;
    case Mult:
      printf( "%s = ", inst->dest->val.stptr->name ); 
      print_operands( inst, "*" );
      break;
    case Div:
      printf( "%s = ", inst->dest->val.stptr->name ); 
      print_operands( inst, "/" );
      break;
    case Assg:
      printf( "%s = ", inst->dest->val.stptr->name ); 
      print_operands( inst, "" );
      break;
    case Gt:
      printf( "if ( " ); 
      print_operands( inst, ">" );
      printf( " ) goto %s", inst->dest->val.goto_label->dest->val.label );
      break;
    case Label: // label instruction
      printf( "%s:", inst->dest->val.label );
      break;
    case Goto: // goto instruction
      printf( "goto %s", inst->dest->val.goto_label->dest->val.label );
      break;
    case Return:
      printf( "Return" );
      break;
    }
    putchar( '\n' );
  }
}

static three_addr_code *code_gen_intcon( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;

  t->place = newtmp();
  op = Assg;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_Intcon;
  operand1->val.iconst = stIntcon( t );
  operand2 = (address *) NULL;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = t->place;
  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  t->code->start = newinstr( op, operand1, operand2, dest, false );
  t->code->end = t->code->start;

  return t->code;
}

static three_addr_code *code_gen_var( tnode *t )
{
  symtabnode *stptr;
  stptr = stVar( t );
  t->place = stptr;
  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  t->code->start = newinstr( Noop, NULL, NULL, NULL, true );
  t->code->end = t->code->start;

  return t->code;
}

static three_addr_code *code_gen_expr( tnode *t )
{
  three_addr_code *tmpcode, *tmpcode2;
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;
  
  tmpcode = code_gen( stBinop_Op1(t) ); // code for operand1
  tmpcode2 = code_gen( stBinop_Op2(t) ); // code for operand2
  
  t->place = newtmp(); // symbol table entry for the value of the expression
  op = t->ntype; // operation type

  /* Generate the quadruple. */
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stBinop_Op1(t)->place;
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_StRef;
  operand2->val.stptr = stBinop_Op2(t)->place;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = t->place;
  
  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  /* Final code = tmpcode || tmpcode2 || newinstr */
  t->code = tmpcode;
  t->code->end->next = tmpcode2->start; // concatenate tmpcode and tmpcode2.
  t->code->end = tmpcode2->end;
  t->code->end->next = newinstr( op, operand1, operand2, dest, false ); // concatenate tmpcode2 and new instruction.
  t->code->end = t->code->end->next; // move end pointer to the new instruction.

  return t->code;
}

static three_addr_code *code_gen_assg( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;

  three_addr_code *tmpcode;
  tmpcode = code_gen( stAssg_Lhs(t) );
  t->code = tmpcode;
  tmpcode = code_gen( stAssg_Rhs(t) );
  t->code->end->next = tmpcode->start;
  t->code->end = tmpcode->end;

  op = Assg;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stAssg_Rhs(t)->place;
  operand2 = NULL;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = stAssg_Lhs(t)->place;
  t->code->end->next = newinstr( op, operand1, operand2, dest, false );
  t->code->end = t->code->end->next;

  return t->code;
}

static three_addr_code *code_gen_arrayref( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;
  three_addr_code *tmpcode2;
  symtabnode *tmp1, *tmp2;
  instr *inst1, *inst2;
  
  tmpcode2 = code_gen( stArraySubscript_Subscript(t) );

  tmp1 = newtmp();
  tmp2 = newtmp(); // hold the offset of array element
  t->place = tmp1; // to be mapped to the memory address

  /* calculate array offset */
  op = Mult;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stArraySubscript_Subscript(t)->place;
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  operand2->val.iconst = INT_SZ;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = tmp2;
  
  inst1 = newinstr( op, operand1, operand2, dest, false );

  op = Plus;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stArraySubscript_Array(t);
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_StRef;
  operand2->val.stptr = tmp2;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = t->place;
  
  inst2 = newinstr( op, operand1, operand2, dest, false );

  /* Glue 4 pieces togeter: tmpcode1 || tmpcode2 || inst1 || inst2. */
  t->code = tmpcode2;
  t->code->end->next = inst1;
  inst1->next = inst2;
  t->code->end = inst2;

  return t->code;
}

static three_addr_code *code_gen_bool( tnode *t, instr *L_then, instr *L_else )
{
  three_addr_code *tmpcode1, *tmpcode2;
  address *dest, *operand1, *operand2;
  instr *inst1, *inst2;
  SyntaxNodeType op;
  
  tmpcode1 = code_gen( stBinop_Op1(t) ); // code for operand1
  tmpcode2 = code_gen( stBinop_Op2(t) ); // code for operand2

  /* Instruction for 'then' statement. */
  op = t->ntype;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stBinop_Op1(t)->place;
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_StRef;
  operand2->val.stptr = stBinop_Op2(t)->place;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_Label;
  dest->val.goto_label = L_then;
  
  inst1 = newinstr( op, operand1, operand2, dest, false );

  /* Instruction for 'else' statement. */
  op = Goto;
  operand1 = NULL;
  operand2 = NULL;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_Label;
  dest->val.goto_label = L_else;
  
  inst2 = newinstr( op, operand1, operand2, dest, false );

  /* Glue 4 pieces together. */
  tmpcode1->end->next = tmpcode2->start;
  tmpcode2->end->next = inst1;
  inst1->next = inst2;
  t->code = tmpcode1;
  t->code->end = inst2;

  return t->code;
}

static three_addr_code *code_gen_ifelse( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;
  three_addr_code *tmpcode1, *tmpcode2, *tmpcode3;
  instr *L_then, *L_else, *L_after, *inst1, *inst2;

  /* Generating code for 'then' statement. */
  L_then = newlabel(); // label instruction for 'then' part.
  tmpcode1 = code_gen( stIf_Then(t) );

  /* Generating code for 'else' statement. */
  L_else = newlabel(); // label instruction for 'else' part.
  tmpcode2 = code_gen( stIf_Else(t) );

  L_after = newlabel(); // label instruction for the 'after' part.

  /* Generating code for relational 'test' statement. */
  tmpcode3 = code_gen_bool( stIf_Test(t), L_then, L_else );
  
  /* Instruction for jumping to then statement. */
  op = Goto;
  operand1 = NULL;
  operand2 = NULL;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_Label;
  dest->val.goto_label = L_after;
  
  inst1 = newinstr( op, operand1, operand2, dest, false );

  /* Glue pieces together. */
  t->code = tmpcode3;
  tmpcode3->end->next = L_then;
  L_then->next = tmpcode1->start;
  tmpcode1->end->next = inst1;
  inst1->next = L_else;
  L_else->next = tmpcode2->start;
  tmpcode2->end->next = L_after;
  t->code->end = L_after;

  return t->code;
}

three_addr_code *code_gen( tnode *t )
{
  symtabnode *stptr;
  tnode *tntmp;
  SyntaxNodeType op;
  address *dest, *operand1, *operand2;
  three_addr_code *tmpcode, *tmpcode2;

  if ( t == NULL ) {
    fprintf( stderr, "null tree node\n" );
    return NULL;
  }

  switch ( t->ntype ) {
  case Error:
    fprintf( stderr, "Error!\n" );
    break;
  case Intcon:
    printf( "Generating code for Intcon...\n" );
    t->code = code_gen_intcon( t );
    break;
  case Var:
    t->code = code_gen_var( t );
    break;
  case BinaryMinus:
  case Mult:
  case Div:
  case Plus:
    printf( "Generating code for plus...\n" );
    t->code = code_gen_expr( t );
    break;    
  case Assg:
    printf( "Generating code for assignment...\n" );
    t->code = code_gen_assg( t );
    break;
  case ArraySubscript:
    printf( "Generating code for array ref...\n" );
    t->code = code_gen_arrayref( t );
    break;
  case If:
    printf( "Generating code for if-else...\n" );
    t->code = code_gen_ifelse( t );
    break;
  case STnodeList:
    printf( "Generating code for statment list...\n" );
    t->code = code_gen( stList_Head(t) );
    for ( tntmp = stList_Rest( t ); tntmp != NULL;
	  tntmp = stList_Rest(tntmp) ) {
      printf( "Generating code for statment list...\n" );
      tmpcode = code_gen( stList_Head(tntmp) );
      t->code->end->next = tmpcode->start;
      t->code->end = tmpcode->end;
    }
    break;
  case Return:
    printf( "Returning....\n" );
    t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
    op = Return;
    operand1 = NULL;
    operand2 = NULL;
    dest = NULL;
    t->code->start = newinstr( op, operand1, operand2, dest, false );
    t->code->end = t->code->start;
    break;
  }

  return t->code;
}
