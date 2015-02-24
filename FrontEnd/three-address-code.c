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

extern void print_code( tnode *t );

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

instr *newfunclabel( const char *funcname )
{
  instr *quad = (instr *) zalloc( sizeof(instr) );
  quad->op = Label;
  quad->dest = (address *) zalloc( sizeof(address) );
  quad->dest->atype = AT_Label;
  sprintf( quad->dest->val.label, "%s", funcname );
  quad->operand1 = NULL;
  quad->operand2 = NULL;
  quad->is_empty = false;
  quad->next = NULL;

  return quad;
}

instr *newenter( symtabnode *func )
{
  instr *quad = (instr *) zalloc( sizeof(instr) );
  quad->op = Enter;
  quad->operand1 = (address *) zalloc( sizeof(address) );
  quad->operand1->atype = AT_StRef;
  quad->operand1->val.stptr = func;
  quad->operand2 = NULL;
  quad->dest = NULL;
  quad->is_empty = false;
  quad->next = NULL;

  return quad;
}

instr *newleave( symtabnode *func )
{
  instr *quad = (instr *) zalloc( sizeof(instr) );
  quad->op = Leave;
  quad->operand1 = (address *) zalloc( sizeof(address) );
  quad->operand1->atype = AT_StRef;
  quad->operand1->val.stptr = func;
  quad->operand2 = NULL;
  quad->dest = NULL;
  quad->is_empty = false;
  quad->next = NULL;

  return quad;
}

static three_addr_code *code_gen_strcon( tnode *t )
{
  char *str = stStringcon(t);

  /* stptr is a global symbol table entry to string constant. */
  symtabnode *stptr = newstrcon( str );

  address *dest, *operand1, *operand2;
  SyntaxNodeType op = Assg;

  t->place = newtmp();

  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_Stringcon;
  operand1->val.stptr = stptr; // point to sym tab entry
  operand2 = (address *) NULL;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = t->place;
  dest->val.stptr->is_strcon = true;

  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  t->code->start = newinstr( op, operand1, operand2, dest, false );
  t->code->end = t->code->start;

  return t->code;
}

static three_addr_code *code_gen_intcon( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;

  t->place = newtmp();
  op = Assg;
  operand1 = (address *) zalloc( sizeof(address) );
  if ( t->ntype == Intcon ) {
    operand1->atype = AT_Intcon;
    operand1->val.iconst = stIntcon( t );
  } else { // charcon
    operand1->atype = AT_Charcon;
    operand1->val.iconst = stCharcon( t );
  }
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

static three_addr_code *code_gen_unary( tnode *t )
{
  three_addr_code *tmpcode;
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;
  
  tmpcode = code_gen( stUnop_Op(t) ); // code for operand1
  
  t->place = newtmp(); // symbol table entry for the value of the expression
  op = t->ntype; // operation type

  /* Generate the quadruple. */
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stUnop_Op(t)->place;
  operand2 = NULL;

  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = t->place;
  
  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  /* Final code = tmpcode || newinstr */
  t->code = tmpcode;
  tmpcode->end->next = newinstr( op, operand1, operand2, dest, false );
  t->code->end = tmpcode->end->next;

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
  tmp1->is_addr = true; // indicate this tmp is an address
  t->place = tmp1; // to be mapped to the memory address

  /* calculate array offset */
  op = Mult;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stArraySubscript_Subscript(t)->place;
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  if ( stArraySubscript_Array(t)->elt_type == t_Int) {
    operand2->val.iconst = INT_SZ;
    t->place->elt_type = t_Int; // record type of array element
  } else { // char array
    operand2->val.iconst = CHAR_SZ;
    t->place->elt_type = t_Char; // record type of array element
  }
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
  instr *inst1, *inst2, *label1;
  SyntaxNodeType op;

  op = t->ntype;

  /* short circuit evaluation for && */
  if ( op == LogicalAnd ) { 
    label1 = newlabel();
    tmpcode1 = code_gen_bool( stBinop_Op1(t), label1, L_else );
    tmpcode2 = code_gen_bool( stBinop_Op2(t), L_then, L_else );
    /* code for && = tmpcode1 || label1 || tmpcode2 */
    t->code = tmpcode1;
    tmpcode1->end->next = label1;
    label1->next = tmpcode2->start;
    t->code->end = tmpcode2->end;
    return t->code;
  }

  /* short circuit evaluation for || */
  if ( op == LogicalOr ) {
    label1 = newlabel();
    tmpcode1 = code_gen_bool( stBinop_Op1(t), L_then, label1 );
    tmpcode2 = code_gen_bool( stBinop_Op2(t), L_then, L_else );
    /* code for && = tmpcode1 || label1 || tmpcode2 */
    t->code = tmpcode1;
    tmpcode1->end->next = label1;
    label1->next = tmpcode2->start;
    t->code->end = tmpcode2->end;
    return t->code;
  }

  /* evaluation for ! */
  if ( op == LogicalNot ) {
    t->code = code_gen_bool( stUnop_Op(t), L_else, L_then );
    return t->code;
  }

  tmpcode1 = code_gen( stBinop_Op1(t) ); // code for operand1
  tmpcode2 = code_gen( stBinop_Op2(t) ); // code for operand2

  /* Instruction for binary relational operation. */
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

  /* Instruction for goto 'else' statement. */
  op = Goto;
  operand1 = NULL;
  operand2 = NULL;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_Label;
  dest->val.goto_label = L_else;
  
  inst2 = newinstr( op, operand1, operand2, dest, false );

  /* Glue 4 pieces together. */
  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  tmpcode1->end->next = tmpcode2->start;
  tmpcode2->end->next = inst1;
  inst1->next = inst2;
  t->code->start = tmpcode1->start;
  t->code->end = inst2;

  return t->code;
}

static three_addr_code *code_gen_ifelse( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;
  three_addr_code *tmpcode1, *tmpcode2, *tmpcode3;
  instr *L_then, *L_else, *L_after, *inst1, *inst2;
  tnode *tnode_else;

  /* Generating code for 'then' statement. */
  L_then = newlabel(); // label instruction for 'then' part.
  tmpcode1 = code_gen( stIf_Then(t) );

  /* Generating code for 'else' statement. */
  L_else = newlabel(); // label instruction for 'else' part.
  tnode_else = stIf_Else( t );
  if ( tnode_else != NULL ) {
    tmpcode2 = code_gen( tnode_else );
  }

  L_after = newlabel(); // label instruction for the 'after' part.

  /* Generating code for relational 'test' statement. */
  if ( tnode_else != NULL ) {
    tmpcode3 = code_gen_bool( stIf_Test(t), L_then, L_else );
  } else {
    tmpcode3 = code_gen_bool( stIf_Test(t), L_then, L_after );
  }

  if ( tnode_else != NULL ) {
  /* Instruction for jumping to after part. */
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
  } else {
    t->code = tmpcode3;
    tmpcode3->end->next = L_then;
    L_then->next = tmpcode1->start;
    tmpcode1->end->next = L_after;
    t->code->end = L_after;
  }

  return t->code;
}

static three_addr_code *code_gen_while( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;
  three_addr_code *tmpcode1, *tmpcode2;
  instr *L_eval, *L_top, *L_after, *inst1;

  L_top = newlabel();
  L_eval = newlabel();
  L_after = newlabel();

  tmpcode1 = code_gen_bool( stWhile_Test(t), L_top, L_after );
  tmpcode2 = code_gen( stWhile_Body(t) );

  /* Instruction for the unconditional jump to L_eval. */
  op = Goto;
  operand1 = NULL;
  operand2 = NULL;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_Label;
  dest->val.goto_label = L_eval;
  
  inst1 = newinstr( op, operand1, operand2, dest, false );

  /* Glue pieces together. */
  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  t->code->start = inst1;
  inst1->next = L_top;
  L_top->next = tmpcode2->start;
  tmpcode2->end->next = L_eval;
  L_eval->next = tmpcode1->start;
  tmpcode1->end->next = L_after;
  t->code->end = L_after;

  return t->code;
}

static three_addr_code *code_gen_for( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;
  three_addr_code *tmpcode1, *tmpcode2, *tmpcode3, *tmpcode4;
  instr *L_eval, *L_top, *L_after, *inst1;

  L_top = newlabel();
  L_eval = newlabel();
  L_after = newlabel();

  tmpcode1 = code_gen( stFor_Init(t) );
  tmpcode2 = code_gen_bool( stFor_Test(t), L_top, L_after );
  tmpcode3 = code_gen( stFor_Body(t) );
  tmpcode4 = code_gen( stFor_Update(t) );

  /* Instruction for the unconditional jump to L_eval. */
  op = Goto;
  operand1 = NULL;
  operand2 = NULL;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_Label;
  dest->val.goto_label = L_eval;
  
  inst1 = newinstr( op, operand1, operand2, dest, false );

  /* Glue pieces together. */
  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  t->code = tmpcode1;
  t->code->end->next = inst1;
  inst1->next = L_top;
  L_top->next = tmpcode3->start;
  tmpcode3->end->next = tmpcode4->start;
  tmpcode4->end->next = L_eval;
  L_eval->next = tmpcode2->start;
  tmpcode2->end->next = L_after;
  t->code->end = L_after;

  return t->code;
}

/* return: non void; args: non void */
static three_addr_code *code_gen_funcall1( tnode *t )
{
  int num_args = 0, i;
  tnode *args = stFunCall_Args( t );
  three_addr_code *tmpcode1;
  instr *inst;
  tnode *tntmp, *arg;
  SyntaxNodeType op;
  address *dest, *operand1, *operand2;
  
  t->place = newtmp(); // place to hold the return value
  tmpcode1 = code_gen( args );

  //  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  t->code = tmpcode1;

  /* Generate code for argument expression and param code one by one. */
  for (tntmp = args; tntmp != NULL; tntmp = stList_Rest(tntmp)) {
    arg = stList_Head( tntmp );
    op = Param;
    operand1 = (address *) zalloc( sizeof(address) );
    operand1->atype = AT_StRef;
    operand1->val.stptr = arg->place;
    operand2 = NULL;
    dest = NULL;
    inst = newinstr( op, operand1, operand2, dest, false );

    t->code->end->next = inst;
    t->code->end = inst;
    
    ++num_args;
  }

  /* call instruction */
  op = Call;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stFunCall_Fun( t ); // symbol table entry for the callee
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  operand2->val.iconst = num_args;
  dest = NULL;
  inst = newinstr( op, operand1, operand2, dest, false );

  t->code->end->next = inst;
  t->code->end = inst;

  /* retrieve instruction */
  op = Retrieve;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = t->place; // symbol table entry for the return value.
  operand2 = NULL;
  dest = NULL;
  inst = newinstr( op, operand1, operand2, dest, false );

  t->code->end->next = inst;
  t->code->end = inst;

  return t->code;
}

/* return: non void; arg: void */
static three_addr_code *code_gen_funcall2( tnode *t )
{
  instr *inst;
  SyntaxNodeType op;
  address *dest, *operand1, *operand2;
  
  t->place = newtmp(); // place to hold the return value
  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );

  /* call instruction */
  op = Call;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stFunCall_Fun( t ); // symbol table entry for the callee
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  operand2->val.iconst = 0;
  dest = NULL;
  inst = newinstr( op, operand1, operand2, dest, false );

  t->code->start = inst;
  t->code->end = t->code->start;

  /* retrieve instruction */
  op = Retrieve;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = t->place; // symbol table entry for the return value.
  operand2 = NULL;
  dest = NULL;
  inst = newinstr( op, operand1, operand2, dest, false );

  t->code->end->next = inst;
  t->code->end = inst;

  return t->code;
}

/* return: void; args: non void */
static three_addr_code *code_gen_funcall3( tnode *t )
{
  int num_args = 0, i;
  tnode *args = stFunCall_Args( t );
  three_addr_code *tmpcode1;
  instr *inst;
  tnode *tntmp, *arg;
  SyntaxNodeType op;
  address *dest, *operand1, *operand2;
  
  tmpcode1 = code_gen( args );

  //  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  t->code = tmpcode1;

  /* Generate code for argument expression and param code one by one. */
  for (tntmp = args; tntmp != NULL; tntmp = stList_Rest(tntmp)) {
    arg = stList_Head( tntmp );
    op = Param;
    operand1 = (address *) zalloc( sizeof(address) );
    operand1->atype = AT_StRef;
    operand1->val.stptr = arg->place;
    operand2 = NULL;
    dest = NULL;
    inst = newinstr( op, operand1, operand2, dest, false );

    t->code->end->next = inst;
    t->code->end = inst;
    
    ++num_args;
  }

  /* call instruction */
  op = Call;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stFunCall_Fun( t ); // symbol table entry for the callee
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  operand2->val.iconst = num_args;
  dest = NULL;
  inst = newinstr( op, operand1, operand2, dest, false );

  t->code->end->next = inst;
  t->code->end = inst;

  return t->code;
}

/* return: void; arg: void */
static three_addr_code *code_gen_funcall4( tnode *t )
{
  instr *inst;
  SyntaxNodeType op;
  address *dest, *operand1, *operand2;
  
  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );

  /* call instruction */
  op = Call;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stFunCall_Fun( t ); // symbol table entry for the callee
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  operand2->val.iconst = 0;
  dest = NULL;
  inst = newinstr( op, operand1, operand2, dest, false );

  t->code->start = inst;
  t->code->end = t->code->start;

  return t->code;
}

static three_addr_code *code_gen_funcall( tnode *t )
{
  tnode *args = stFunCall_Args( t );
  symtabnode *stptr = stFunCall_Fun(t); // sym tab entry for the callee.
  int ret_type = stptr->ret_type; // return type of the callee.

  if ( args != NULL && ret_type != t_None ) {
    return code_gen_funcall1( t );
  } else if ( args == NULL && ret_type != t_None ) {
    return code_gen_funcall2( t );
  } else if ( args != NULL && ret_type == t_None ) {
    return code_gen_funcall3( t );
  } else {
    return code_gen_funcall4( t );
  }
}

static three_addr_code *code_gen_return( tnode *t )
{
  tnode *return_expr = stReturn( t );
  t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
  three_addr_code *tmpcode;
  address *dest, *operand1, *operand2;
  SyntaxNodeType op;

  op = Return;
  if ( return_expr == NULL ) { // return type is void
    operand1 = NULL;
    operand2 = NULL;
    dest = NULL;
    t->code->start = newinstr( op, operand1, operand2, dest, false );
    t->code->end = t->code->start;
    return t->code;
  } else {
    tmpcode = code_gen( return_expr );
    operand1 = (address *) zalloc( sizeof(address) );
    operand1->atype = AT_StRef;
    operand1->val.stptr = return_expr->place; // symbol table entry for the value to be returned
    operand2 = NULL;
    dest = NULL;
    t->code->start = tmpcode->start;
    tmpcode->end->next = newinstr( op, operand1, operand2, dest, false );
    t->code->end = tmpcode->end->next;
    return t->code;
  }
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
  case Charcon:
  case Intcon:
    t->code = code_gen_intcon( t );
    break;
  case Stringcon:
    t->code = code_gen_strcon( t );
    break;
  case Var:
    t->code = code_gen_var( t );
    break;
  case BinaryMinus:
  case Mult:
  case Div:
  case Plus:
    t->code = code_gen_expr( t );
    break;
  case UnaryMinus:
    t->code = code_gen_unary( t );
    break;
  case Assg:
    t->code = code_gen_assg( t );
    break;
  case ArraySubscript:
    t->code = code_gen_arrayref( t );
    break;
  case If:
    t->code = code_gen_ifelse( t );
    break;
  case While:
    t->code = code_gen_while( t );
    break;
  case For:
    t->code = code_gen_for( t );
    break;
  case FunCall:
    t->code = code_gen_funcall( t );
    break;
  case STnodeList:
    t->code = code_gen( stList_Head(t) );
    for ( tntmp = stList_Rest( t ); tntmp != NULL;
	  tntmp = stList_Rest(tntmp) ) {
      tmpcode = code_gen( stList_Head(tntmp) );
      t->code->end->next = tmpcode->start;
      t->code->end = tmpcode->end;
    }
    break;
  case Return:
    t->code = code_gen_return( t );
    break;
  default:
    fprintf(stderr, "Unknown syntax tree node type %d\n", t->ntype);
  }

  return t->code;
}
