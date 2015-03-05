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

#define LABEL_PREFIX "_L"

extern void print_TAC_seq( tnode *t, bool reverse );

extern int tmpvar_counter; // for tmp variable reuse purpose
int label_counter = 0; // counter for the labels.

/* Generate a sequence of TAC for the syntax tree node 't'. */
TAC_seq *code_gen( tnode *t );

/**
 * Create a single three-address-code instruction.
 */
TAC *newTAC( SyntaxNodeType optype, address *operand1,
	     address *operand2, address *dest )
{
  TAC *tac = (TAC *) zalloc( sizeof(TAC) );
  tac->optype = optype;
  tac->dest = dest;
  tac->operand1 = operand1;
  tac->operand2 = operand2;
  tac->prev = NULL;
  tac->next = NULL;

  return tac;
}

/**
 * Return a compiler generated label
 * represented by a three-address-code instruction.
 */
TAC *newlabel()
{
  TAC *tac = (TAC *) zalloc( sizeof(TAC) );
  tac->optype = Label;
  tac->dest = (address *) zalloc( sizeof(address) );
  tac->dest->atype = AT_Label;
  // 10 bytes is enough to hold a compiler generated label.
  tac->dest->val.label = (char *) zalloc( 10 ); 
  sprintf( tac->dest->val.label, "%s%d", LABEL_PREFIX, label_counter++ );
  tac->operand1 = NULL; // not needed
  tac->operand2 = NULL; // not needed
  tac->prev = NULL;
  tac->next = NULL;

  return tac;
}

/**
 * Return a TAC instruction for function labels.
 */
TAC *newfunclabel( const char *funcname )
{
  TAC *quad = (TAC *) zalloc( sizeof(TAC) );
  quad->optype = Label;
  quad->dest = (address *) zalloc( sizeof(address) );
  quad->dest->atype = AT_Label;
  quad->dest->val.label = (char *) zalloc( strlen(funcname) + 1 );
  sprintf( quad->dest->val.label, "%s", funcname );
  quad->operand1 = NULL;
  quad->operand2 = NULL;
  quad->next = NULL;

  return quad;
}

/**
 * Return a TAC instruction for entering a function is pointed
 * by symbol table entry 'func'.
 */
TAC *enter_func( symtabnode *func )
{
  TAC *quad = (TAC *) zalloc( sizeof(TAC) );
  quad->optype = Enter;
  quad->operand1 = (address *) zalloc( sizeof(address) );
  quad->operand1->atype = AT_StRef;
  quad->operand1->val.stptr = func;
  quad->operand2 = NULL;
  quad->dest = NULL;
  quad->next = NULL;

  return quad;
}

/**
 * Generate code for string constant.
 */
static TAC_seq *code_gen_strcon( tnode *t )
{
  char *str = stStringcon(t);

  /* stptr is a global symbol table entry to string constant. */
  symtabnode *stptr = newtmp_strcon( str );
  t->place = stptr;

  address *dest, *operand1, *operand2;
  SyntaxNodeType optype = Stringcon;

  operand1 = NULL; // not needed
  operand2 = (address *) NULL;
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_Stringcon;
  dest->val.stptr = stptr; // point to sym tab entry

  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  t->tac_seq->start = newTAC( optype, operand1, operand2, dest );
  t->tac_seq->end = t->tac_seq->start;

  return t->tac_seq;
}

/**
 * Generating code for integer constants. 't' is either a 'Intcon'
 * node or a 'Charcon' node.
 *
 * Examples: 
 * _tvar0 = 50
 * _tvar1 = 'c'
 */
static TAC_seq *code_gen_intcon( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType optype;

  t->place = newtmp_var(); // symbol table entry for holding the constant value
  optype = Assg; // assign constant to a tmp variable

  /* Fill in operand1 with constant value. */
  operand1 = (address *) zalloc( sizeof(address) );
  if ( t->ntype == Intcon ) {
    operand1->atype = AT_Intcon; // integer constant
    operand1->val.iconst = stIntcon( t );
  } else { // charcon
    operand1->atype = AT_Charcon; // char constant
    operand1->val.iconst = stCharcon( t );
  }
  
  operand2 = (address *) NULL; // not needed

  /* Fill in dest with newly created tmp variable. */
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = t->place;

  /* Create a new TAC instruction and add it to TAC sequence for node 't'. */
  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  t->tac_seq->start = newTAC( optype, operand1, operand2, dest );
  t->tac_seq->end = t->tac_seq->start;

  return t->tac_seq;
}

/**
 * Generate code for int or char variables where 't' is a syntax tree
 * node representing a variable.
 */
static TAC_seq *code_gen_var( tnode *t )
{
  symtabnode *stptr;
  stptr = stVar( t );
  t->place = stptr;
  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  /* Indicate operation type is Noop. */
  t->tac_seq->start = newTAC( Noop, NULL, NULL, NULL );
  t->tac_seq->end = t->tac_seq->start;

  return t->tac_seq;
}

/**
 * Generate TAC sequence for expressions.
 * For example: x + y; 5 + A[1]; (x+y) * (x-y).
 */
static TAC_seq *code_gen_expr( tnode *t )
{
  TAC_seq *tacseq_op1, *tacseq_op2;
  address *dest, *operand1, *operand2;
  TAC *tac_assg;
  SyntaxNodeType optype;
  
  tacseq_op1 = code_gen( stBinop_Op1(t) ); // code for operand1
  tacseq_op2 = code_gen( stBinop_Op2(t) ); // code for operand2

  /* Generate TAC for: operand1 optype operand2. */
  optype = t->ntype; // in this case, TAC operation type is also syntax tree node type.
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stBinop_Op1(t)->place;
  if ( operand1->val.stptr->type == t_Tmp_Var ) {
    /* if a tmp variable with type of t_Tmp_Var appears on the RHS,
       this means we can reuse it. So decrement counter by 1. */
    --tmpvar_counter;
  }

  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_StRef;
  operand2->val.stptr = stBinop_Op2(t)->place;
  if ( operand2->val.stptr->type == t_Tmp_Var ) {
    /* if a tmp variable with type of t_Tmp_Var appears on the RHS,
       this means we can reuse it. So decrement counter by 1. */
    --tmpvar_counter;
  }

  t->place = newtmp_var(); // symbol table entry for the value of the expression
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = t->place;

  tac_assg = newTAC( optype, operand1, operand2, dest );

  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  /* Final code = tacseq_op1 || tacseq_op2 || tac_assg */
  tacseq_op1->end->next = tacseq_op2->start;
  tacseq_op2->start->prev = tacseq_op1->end;
  tacseq_op2->end->next = tac_assg;
  tac_assg->prev = tacseq_op2->end;

  t->tac_seq->start = tacseq_op1->start;
  t->tac_seq->end = tac_assg;
  
  return t->tac_seq;
}

/**
 * Generate TAC sequence for unary minus. For example: -x; -5; -(A[0]*z)
 */
static TAC_seq *code_gen_unaryminus( tnode *t )
{
  TAC_seq *tacseq_unop;
  TAC *tac_minus;
  address *dest, *operand1, *operand2;
  SyntaxNodeType optype;
  
  tacseq_unop = code_gen( stUnop_Op(t) ); // code for operand
  t->place = newtmp_var(); // symbol table entry for the value of the unary minus.

  /* TAC for unary minus. */
  optype = t->ntype; // operation type
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stUnop_Op(t)->place;
  if ( operand1->val.stptr->type == t_Tmp_Var ) {
    /* if a tmp variable with type of t_Tmp_Var appears on the RHS,
       this means we can reuse it. So decrement counter by 1. */
    --tmpvar_counter;
  }
  
  operand2 = NULL; // not needed

  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = t->place;

  tac_minus = newTAC( optype, operand1, operand2, dest );
  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  
  /* Final code = tacseq_unop || tac_minus */
  tacseq_unop->end->next = tac_minus;
  tac_minus->prev = tacseq_unop->end;
  t->tac_seq->start = tacseq_unop->start;
  t->tac_seq->end = tac_minus;

  return t->tac_seq;
}

/**
 * Generate code sequence for assignment (LHS = RHS). 
 * For example: x = 5; y = A[3]; B[2] = x+y; g = A[2] + B[1];
 *
 * Note that in C-- only char/int variables or array elements can
 * appear in the LHS. And for char/int variables, no need to generate
 * TAC for it, just need their symbol table entries.
 *
 * Final TAC sequence genereated is:
 * (TAC sequence for LHS) || (TAC sequence for RHS) || (TAC for LHS = RHS)
 */
static TAC_seq *code_gen_assg( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType optype;
  TAC_seq *tacseq_lhs, *tacseq_rhs;
  TAC *tac_assg;

  tacseq_rhs = code_gen( stAssg_Rhs(t) ); // Generate code for RHS.

  /* Generate TAC for LHS = RHS */
  optype = Assg;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef; // RHS must be symbol table entry
  operand1->val.stptr = stAssg_Rhs(t)->place;
  if ( operand1->val.stptr->type == t_Tmp_Var ) {
    /* if a tmp variable with type of t_Tmp_Var appears on the RHS,
       this means we can reuse it. So decrement counter by 1. */
    --tmpvar_counter;
  }

  tacseq_lhs = code_gen( stAssg_Lhs(t) ); // Generate code for LHS.
    
  operand2 = NULL; // not needed
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef; // LHS must be symbol table entry
  dest->val.stptr = stAssg_Lhs(t)->place;
  tac_assg = newTAC( optype, operand1, operand2, dest );

  /* Glue three piece together. */
  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );

  /* LHS code || RHS code */
  tacseq_lhs->end->next = tacseq_rhs->start;
  tacseq_rhs->start->prev = tacseq_lhs->end;

  /* RHS code || tac: LHS=RHS */
  tacseq_rhs->end->next = tac_assg;
  tac_assg->prev = tacseq_rhs->end;

  /* Place start and end pointers. */
  t->tac_seq->start = tacseq_lhs->start;
  t->tac_seq->end = tac_assg;

  return t->tac_seq;
}

/**
 * Generate TAC sequence for array reference.
 * For example: A[3]; A[i]; A[i+1], A[A[0]] etc.
 */
static TAC_seq *code_gen_arrayref( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType optype;
  TAC_seq *tacseq_sub;
  symtabnode *tmp_addr, *tmp_offset;
  TAC *tac_offset, *tac_addr;

  /* Generate code for array subscript expression. */
  tacseq_sub = code_gen( stArraySubscript_Subscript(t) );

  tmp_addr = newtmp_addr(); // tmp for holding array address
  t->place = tmp_addr; // to be mapped to the memory address

  /*
   * TAC for calculating array offset: dest = operand1 * operand2.
   */ 
  optype = Mult;
  /* operand1 holds the value of array subscription.
     It could be a tmp variable or a tmp address in the case A[A[0]]. */
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stArraySubscript_Subscript(t)->place;
  if ( operand1->val.stptr->type == t_Tmp_Var ) {
    /* if a tmp variable with type of t_Tmp_Var appears on the RHS,
       this means we can reuse it. So decrement counter by 1. */
    --tmpvar_counter;
  }

  /* operand2 holds the size of an array element. */
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  if ( stArraySubscript_Array(t)->elt_type == t_Int) {
    operand2->val.iconst = INT_SZ;
    t->place->elt_type = t_Int; // record type of array element
  } else { // char array
    operand2->val.iconst = CHAR_SZ;
    t->place->elt_type = t_Char; // record type of array element
  }

  tmp_offset = newtmp_var(); // tmp for holding the offset of array element
  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = tmp_offset;
  
  tac_offset = newTAC( optype, operand1, operand2, dest );

  /*
   * TAC for calculating address of array element: dest = operand1 + operand2.
   */
  optype = Plus;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stArraySubscript_Array(t); // symbol table entry for array
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_StRef;
  operand2->val.stptr = tmp_offset; // operand2 is the offset
  if ( operand2->val.stptr->type == t_Tmp_Var ) {
    /* if a tmp variable with type of t_Tmp_Var appears on the RHS,
       this means we can reuse it. So decrement counter by 1. */
    --tmpvar_counter;
  }

  dest = (address *) zalloc( sizeof(address) );
  dest->atype = AT_StRef;
  dest->val.stptr = t->place; // hold the address for the element
  
  tac_addr = newTAC( optype, operand1, operand2, dest );

  /* Glue 3 pieces togeter: tacseq_sub || tac_offset || tac_addr. */
  tacseq_sub->end->next = tac_offset;
  tac_offset->prev = tacseq_sub->end;
  tac_offset->next = tac_addr;
  tac_addr->prev = tac_offset;
  
  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );  
  t->tac_seq->start = tacseq_sub->start;
  t->tac_seq->end = tac_addr;

  return t->tac_seq;
}

/**
 * Generate code for a boolean operation represented by a syntax tree node 't'.
 * If the evalution is true, branch to label 'L_then', otherwise to 'L_else'.
 */
static TAC_seq *code_gen_bool( tnode *t, TAC *L_then, TAC *L_else )
{
  TAC_seq *tacseq_op1, *tacseq_op2;
  address *dest, *operand1, *operand2;
  TAC *tac_then, *tac_else, *transit_label;
  SyntaxNodeType optype;

  optype = t->ntype;
  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );

  /* short circuit evaluation for &&. e.g. x > y && n != 0 */
  if ( optype == LogicalAnd ) { 
    transit_label = newlabel();
    tacseq_op1 = code_gen_bool( stBinop_Op1(t), transit_label, L_else );
    tacseq_op2 = code_gen_bool( stBinop_Op2(t), L_then, L_else );
    /* code for &&: tacseq_op1 || transit_label || tacseq_op2 */
    tacseq_op1->end->next = transit_label;
    transit_label->prev = tacseq_op1->end;
    transit_label->next = tacseq_op2->start;
    tacseq_op2->start->prev = transit_label;

    t->tac_seq->start = tacseq_op1->start;
    t->tac_seq->end = tacseq_op2->end;
    return t->tac_seq;
  }

  /* short circuit evaluation for || */
  if ( optype == LogicalOr ) {
    transit_label = newlabel();
    tacseq_op1 = code_gen_bool( stBinop_Op1(t), L_then, transit_label );
    tacseq_op2 = code_gen_bool( stBinop_Op2(t), L_then, L_else );
    /* code for &&: tacseq_op1 || transit_label || tacseq_op2 */
    tacseq_op1->end->next = transit_label;
    transit_label->prev = tacseq_op1->end;
    transit_label->next = tacseq_op2->start;
    tacseq_op2->start->prev = transit_label;

    t->tac_seq->start = tacseq_op1->start;
    t->tac_seq->end = tacseq_op2->end;
    return t->tac_seq;
  }

  /* evaluation for ! */
  if ( optype == LogicalNot ) {
    t->tac_seq = code_gen_bool( stUnop_Op(t), L_else, L_then );
    return t->tac_seq;
  }

  /* 
   * Following are boolean operations other than &&, || and !.
   */

  tacseq_op1 = code_gen( stBinop_Op1(t) ); // code for operand1
  tacseq_op2 = code_gen( stBinop_Op2(t) ); // code for operand2

  /* Instruction for binary relational operation: if (B) goto L_then */
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stBinop_Op1(t)->place;
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_StRef;
  operand2->val.stptr = stBinop_Op2(t)->place;
  dest = L_then->dest;
  tac_then = newTAC( optype, operand1, operand2, dest );

  /* Instruction for goto 'else' statement. */
  optype = Goto;
  operand1 = NULL;
  operand2 = NULL;
  dest = L_else->dest;
  
  tac_else = newTAC( optype, operand1, operand2, dest );

  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  /* Glue 4 pieces together: tacseq_op1 || tacseq_op2 || tac_then || tac_else */
  tacseq_op1->end->next = tacseq_op2->start;
  tacseq_op2->start->prev = tacseq_op1->end;

  tacseq_op2->end->next = tac_then;
  tac_then->prev = tacseq_op2->end;

  tac_then->next = tac_else;
  tac_else->prev = tac_then;

  t->tac_seq->start = tacseq_op1->start;
  t->tac_seq->end = tac_else;

  return t->tac_seq;
}

/**
 * Generate code for syntax tree node 't' that represents a 'if' statement.
 */
static TAC_seq *code_gen_ifelse( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType optype;
  TAC_seq *tacseq_then, *tacseq_else, *tacseq_test;
  TAC *L_then, *L_else, *L_after, *tac_goto_after;
  tnode *tnode_else;

  L_then = newlabel(); // label for 'then' statement

  tnode_else = stIf_Else( t ); 
  if ( tnode_else != NULL ) {
    L_else = newlabel(); // label for 'else' statement.
  }

  L_after = newlabel(); // label for the 'after' statement.

  /* Generating code for binary relation 'test' statement. */
  if ( tnode_else != NULL ) {
    tacseq_test = code_gen_bool( stIf_Test(t), L_then, L_else );
  } else {
    tacseq_test = code_gen_bool( stIf_Test(t), L_then, L_after );
  }

  tacseq_then = code_gen( stIf_Then(t) ); // code for 'then' statement
  if ( tnode_else != NULL ) {
    tacseq_else = code_gen( tnode_else ); // code for 'else' statement.
  }

  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  if ( tnode_else != NULL ) { /* Instruction for jumping to 'after' label. */
    optype = Goto;
    operand1 = NULL;
    operand2 = NULL;
    dest = L_after->dest;
  
    tac_goto_after = newTAC( optype, operand1, operand2, dest );

    /* Glue pieces together:
       tacseq_test || L_then || tacseq_then || tac_goto_after
       || L_else || tacseq_else || L_after */
    tacseq_test->end->next = L_then;
    L_then->prev = tacseq_test->end;
    
    L_then->next = tacseq_then->start;
    tacseq_then->start->prev = L_then;

    tacseq_then->end->next = tac_goto_after;
    tac_goto_after->prev = tacseq_then->end;

    tac_goto_after->next = L_else;
    L_else->prev = tac_goto_after;
    L_else->next = tacseq_else->start;
    tacseq_else->start->prev = L_else;

    tacseq_else->end->next = L_after;
    L_after->prev = tacseq_else->end;
  } else { // else part is empty
    /* Glue pieces together:
       tacseq_test || L_then || tacseq_then || L_after */
    tacseq_test->end->next = L_then;
    L_then->prev = tacseq_test->end;
    
    L_then->next = tacseq_then->start;
    tacseq_then->start->prev = L_then;

    tacseq_then->end->next = L_after;
    L_after->prev = tacseq_then->end;
  }
  t->tac_seq->start = tacseq_test->start;
  t->tac_seq->end = L_after;

  return t->tac_seq;
}

/**
 * Generate code for a while statement.
 */
static TAC_seq *code_gen_while( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType optype;
  TAC_seq *tacseq_test, *tacseq_body;
  TAC *L_eval, *L_top, *L_after, *tac_gotoeval;

  L_top = newlabel();
  L_eval = newlabel();
  L_after = newlabel();

  tacseq_test = code_gen_bool( stWhile_Test(t), L_top, L_after );
  tacseq_body = code_gen( stWhile_Body(t) );

  /* Instruction for the unconditional jump to L_eval. */
  optype = Goto;
  operand1 = NULL;
  operand2 = NULL;
  dest = L_eval->dest;
  
  tac_gotoeval = newTAC( optype, operand1, operand2, dest );

  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  /* Glue pieces together: tac_gotoeval || L_top || tacseq_body
     || L_eval || tacseq_test || L_after  */
  tac_gotoeval->next = L_top;
  L_top->prev = tac_gotoeval;
  
  L_top->next = tacseq_body->start;
  tacseq_body->start->prev = L_top;

  tacseq_body->end->next = L_eval;
  L_eval->prev = tacseq_body->end;
  
  L_eval->next = tacseq_test->start;
  tacseq_test->start->prev = L_eval;
  
  tacseq_test->end->next = L_after;
  L_after->prev = tacseq_test->end;

  t->tac_seq->start = tac_gotoeval;
  t->tac_seq->end = L_after;

  return t->tac_seq;
}

/**
 * Generate TAC sequence for 'for' statement.
 */
static TAC_seq *code_gen_for( tnode *t )
{
  address *dest, *operand1, *operand2;
  SyntaxNodeType optype;
  TAC_seq *tacseq_init, *tacseq_test, *tacseq_body, *tacseq_update;
  TAC *L_eval, *L_top, *L_after, *tac_gotoeval;

  L_top = newlabel();
  L_eval = newlabel();
  L_after = newlabel();

  tacseq_init = code_gen( stFor_Init(t) );
  tacseq_test = code_gen_bool( stFor_Test(t), L_top, L_after );
  tacseq_body = code_gen( stFor_Body(t) );
  tacseq_update = code_gen( stFor_Update(t) );

  /* Instruction for the unconditional jump to L_eval. */
  optype = Goto;
  operand1 = NULL;
  operand2 = NULL;
  dest = L_eval->dest;
  tac_gotoeval = newTAC( optype, operand1, operand2, dest );

  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  /* Glue pieces together: tacseq_init || tac_gotoeval || L_top
     || tacseq_body || tacseq_update || L_eval || tacseq_test || L_after. */
  tacseq_init->end->next = tac_gotoeval;
  tac_gotoeval->prev = tacseq_init->end;
  
  tac_gotoeval->next = L_top;
  L_top->prev = tac_gotoeval;
  
  L_top->next = tacseq_body->start;
  tacseq_body->start->prev = L_top;
  
  tacseq_body->end->next = tacseq_update->start;
  tacseq_update->start->prev = tacseq_body->end;
  
  tacseq_update->end->next = L_eval;
  L_eval->prev = tacseq_update->end;
  
  L_eval->next = tacseq_test->start;
  tacseq_test->start->prev = L_eval;
  
  tacseq_test->end->next = L_after;
  L_after->prev = tacseq_test->end;

  t->tac_seq->start = tacseq_init->start;
  t->tac_seq->end = L_after;

  return t->tac_seq;
}

/* return: non void; args: non void */
static TAC_seq *code_gen_funcall1( tnode *t )
{
  int num_args = 0;
  tnode *args = stFunCall_Args( t );
  TAC_seq *tacseq_args;
  TAC *tac_param, *tac_call, *tac_retrieve;
  tnode *tntmp, *arg;
  SyntaxNodeType optype;
  address *dest, *operand1, *operand2;
  
  t->place = newtmp_var(); // place to hold the return value
  tacseq_args = code_gen( args ); // code for evaluating arguments

  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  t->tac_seq->start = tacseq_args->start;
  t->tac_seq->end = tacseq_args->end;

  /* Generate code for argument expression and param code one by one. */
  for (tntmp = args; tntmp != NULL; tntmp = stList_Rest(tntmp)) {
    arg = stList_Head( tntmp );
    optype = Param;
    operand1 = (address *) zalloc( sizeof(address) );
    operand1->atype = AT_StRef;
    operand1->val.stptr = arg->place;
    operand2 = NULL;
    dest = NULL;
    tac_param = newTAC( optype, operand1, operand2, dest );

    /* Chain TAC one by one. */
    t->tac_seq->end->next = tac_param;
    tac_param->prev = t->tac_seq->end;
    t->tac_seq->end = tac_param;
    
    ++num_args;
  }

  /* TAC for calling func */
  optype = Call;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stFunCall_Fun( t ); // symbol table entry for the callee
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  operand2->val.iconst = num_args;
  dest = NULL;
  tac_call = newTAC( optype, operand1, operand2, dest );

  /* chain TACs */
  t->tac_seq->end->next = tac_call;
  tac_call->prev = t->tac_seq->end;
  t->tac_seq->end = tac_call;

  /* TAC for retrieving return value */
  optype = Retrieve;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = t->place; // symbol table entry for the return value.
  /* Can we reuse this tmp variable? No! This value has yet to be assigned.*/
  operand2 = NULL;
  dest = NULL;
  tac_retrieve = newTAC( optype, operand1, operand2, dest );

  /* chain TACs */
  t->tac_seq->end->next = tac_retrieve;
  tac_retrieve->prev = t->tac_seq->end;
  t->tac_seq->end =tac_retrieve;

  return t->tac_seq;
}

/* return: non void; arg: void */
static TAC_seq *code_gen_funcall2( tnode *t )
{
  TAC *tac_call, *tac_retrieve;
  SyntaxNodeType optype;
  address *dest, *operand1, *operand2;
  
  t->place = newtmp_var(); // place to hold the return value
  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );

  /* TAC for calling the callee. */
  optype = Call;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stFunCall_Fun( t ); // symbol table entry for the callee
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  operand2->val.iconst = 0;
  dest = NULL;
  tac_call = newTAC( optype, operand1, operand2, dest );

  t->tac_seq->start = tac_call;
  t->tac_seq->end = tac_call;

  /* retrieve instruction */
  optype = Retrieve;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = t->place; // symbol table entry for the return value.
  operand2 = NULL;
  dest = NULL;
  tac_retrieve = newTAC( optype, operand1, operand2, dest );

  t->tac_seq->end->next = tac_retrieve;
  tac_retrieve->prev = t->tac_seq->end;
  t->tac_seq->end = tac_retrieve;

  return t->tac_seq;
}

/* return: void; args: non void */
static TAC_seq *code_gen_funcall3( tnode *t )
{
  int num_args = 0;
  tnode *args = stFunCall_Args( t );
  TAC_seq *tacseq_args;
  TAC *tac_param, *tac_call;
  tnode *tntmp, *arg;
  SyntaxNodeType optype;
  address *dest, *operand1, *operand2;
  
  tacseq_args = code_gen( args ); // code for evaluating arguments

  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  t->tac_seq->start = tacseq_args->start;
  t->tac_seq->end = tacseq_args->end;

  /* Generate code for argument expression and param code one by one. */
  for (tntmp = args; tntmp != NULL; tntmp = stList_Rest(tntmp)) {
    arg = stList_Head( tntmp );
    optype = Param;
    operand1 = (address *) zalloc( sizeof(address) );
    operand1->atype = AT_StRef;
    operand1->val.stptr = arg->place;
    operand2 = NULL;
    dest = NULL;
    tac_param = newTAC( optype, operand1, operand2, dest );

    /* Chain TAC one by one. */
    t->tac_seq->end->next = tac_param;
    tac_param->prev = t->tac_seq->end;
    t->tac_seq->end = tac_param;
    
    ++num_args;
  }

  /* TAC for calling func */
  optype = Call;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stFunCall_Fun( t ); // symbol table entry for the callee
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  operand2->val.iconst = num_args;
  dest = NULL;
  tac_call = newTAC( optype, operand1, operand2, dest );

  /* chain TACs */
  t->tac_seq->end->next = tac_call;
  tac_call->prev = t->tac_seq->end;
  t->tac_seq->end = tac_call;

  return t->tac_seq;
}

/* return: void; arg: void */
static TAC_seq *code_gen_funcall4( tnode *t )
{
  TAC *tac_call;
  SyntaxNodeType optype;
  address *dest, *operand1, *operand2;
  
  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );

  /* call instruction */
  optype = Call;
  operand1 = (address *) zalloc( sizeof(address) );
  operand1->atype = AT_StRef;
  operand1->val.stptr = stFunCall_Fun( t ); // symbol table entry for the callee
  operand2 = (address *) zalloc( sizeof(address) );
  operand2->atype = AT_Intcon;
  operand2->val.iconst = 0;
  dest = NULL;
  tac_call = newTAC( optype, operand1, operand2, dest );

  t->tac_seq->start = tac_call;
  t->tac_seq->end = tac_call;

  return t->tac_seq;
}

/**
 * Generate TAC sequence for function calls.
 */
static TAC_seq *code_gen_funcall( tnode *t )
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

/**
 * Generate TAC sequence for return statement.
 */
static TAC_seq *code_gen_return( tnode *t )
{
  tnode *return_expr = stReturn( t );
  t->tac_seq = (TAC_seq *) zalloc( sizeof(TAC_seq) );
  TAC_seq *tmpcode;
  TAC *tac_ret;
  address *dest, *operand1, *operand2;
  SyntaxNodeType optype;

  optype = Return;
  if ( return_expr == NULL ) { // return type is void
    operand1 = NULL;
    operand2 = NULL;
    dest = NULL;
    t->tac_seq->start = newTAC( optype, operand1, operand2, dest );
    t->tac_seq->end = t->tac_seq->start;
    return t->tac_seq;
  } else {
    tmpcode = code_gen( return_expr );
    operand1 = (address *) zalloc( sizeof(address) );
    operand1->atype = AT_StRef;
    operand1->val.stptr = return_expr->place; // symbol table entry for the value to be returned
    operand2 = NULL;
    dest = NULL;
    
    t->tac_seq->start = tmpcode->start;
    tac_ret = newTAC( optype, operand1, operand2, dest );
    tmpcode->end->next = tac_ret;
    tac_ret->prev = tmpcode->end;
    t->tac_seq->end = tac_ret;
    return t->tac_seq;
  }
}

TAC_seq *code_gen( tnode *t )
{
  tnode *tntmp;
  TAC_seq *tmpcode;

  if ( t == NULL ) {
    fprintf( stderr, "null tree node\n" );
    return NULL;
  }

  switch ( t->ntype ) {
  case Error:
    fprintf( stderr, "Wrong syntax tree node type!\n" );
    break;
  case Charcon:
  case Intcon: // done
    t->tac_seq = code_gen_intcon( t );
    break;
  case Stringcon: // done
    t->tac_seq = code_gen_strcon( t );
    break;
  case Var: // done
    t->tac_seq = code_gen_var( t );
    break;
  case BinaryMinus:
  case Mult:
  case Div:
  case Plus: // done
    t->tac_seq = code_gen_expr( t );
    break;
  case UnaryMinus: // done
    t->tac_seq = code_gen_unaryminus( t );
    break;
  case Assg: // done
    t->tac_seq = code_gen_assg( t );
    break;
  case ArraySubscript: // done
    t->tac_seq = code_gen_arrayref( t );
    break;
  case If: // done
    t->tac_seq = code_gen_ifelse( t );
    break;
  case While: // done
    t->tac_seq = code_gen_while( t );
    break;
  case For: // done
    t->tac_seq = code_gen_for( t );
    break;
  case FunCall: // done
    t->tac_seq = code_gen_funcall( t );
    break;
  case STnodeList: // done
    t->tac_seq = code_gen( stList_Head(t) );
    for ( tntmp = stList_Rest( t ); tntmp != NULL;
	  tntmp = stList_Rest(tntmp) ) {
      tmpcode = code_gen( stList_Head(tntmp) );
      t->tac_seq->end->next = tmpcode->start;
      tmpcode->start->prev = t->tac_seq->end;
      t->tac_seq->end = tmpcode->end;
    }
    break;
  case Return: // done
    t->tac_seq = code_gen_return( t );
    break;
  default:
    fprintf(stderr, "Unknown syntax tree node type %d\n", t->ntype);
  }

  return t->tac_seq;
}
