/*
 * print.c
 * code to print stuff out.
 *
 * Author: Saumya Debray
 */
#include <stdarg.h>
#include "global.h"
#include "protos.h"
#include "syntax-tree.h"
#include "basic_block.h"
#include "bitvector.h"

static void indent(int n);
static void printBinop(int op);
static void printUnop(int op);

extern bbl *bhead;
extern int num_defuses;
extern int num_vars;

/*
 * printSyntaxTree(t,n) -- print out a syntax tree.  t is a pointer
 * to the syntax tree to be printed out, n gives the no. of spaces
 * of indentation to provide before printing t.
 * 
 */
void printSyntaxTree(tnode *t, int n, int depth)
{
  symtabnode *stptr;
  tnode *tntmp0;

  printf("%d:", depth);
  indent(n);

  if (t == NULL) {
    printf("-null-\n");
    return;
  }

  switch (t->ntype) {
  case Error:
    printf("-error-\n");
    break;

  case Intcon:
    printf("intcon(%d);\n", stIntcon(t));
    break;

  case Charcon:
    printf("charcon(%d);\n", stCharcon(t));
    break;

  case Stringcon:
    printf("str(%s);\n", stStringcon(t));
    break;

  case Var:
    stptr = stVar(t);
    printf("id(name=%s, scope=%s);\n", 
	   stptr->name,
	   (stptr->scope == Global ? "G" : "L"));
    break;

  case ArraySubscript:
    stptr = stArraySubscript_Array(t);
    printf("arrayRef(id(name=%s, scope=%s),\n",
	   stptr->name,
	   (stptr->scope == Global ? "G" : "L"));
    printSyntaxTree(stArraySubscript_Subscript(t), n+9, depth+1);
    printf("%d:", depth);
    indent(n+8);
    printf(")\n");
    break;

  case UnaryMinus:
  case LogicalNot:
    printUnop(t->ntype);
    printf("(\n");
    printSyntaxTree(stUnop_Op(t), n+2, depth+1);
    printf("%d:", depth);
    indent(n);
    printf(")\n");
    break;

  case Plus:
  case BinaryMinus:
  case Mult:
  case Div:
  case Equals:
  case Neq:
  case Leq:
  case Lt:
  case Geq:
  case Gt:
  case LogicalAnd:
  case LogicalOr:
    printBinop(t->ntype);
    printf("(\n");
    printSyntaxTree(stBinop_Op1(t), n+2, depth+1);
    printSyntaxTree(stBinop_Op2(t), n+2, depth+1);
    printf("%d:", depth);
    indent(n);
    printf(")\n");
    break;

  case FunCall:
    stptr = stFunCall_Fun(t);
    printf("CALL: callee=%s\n", stptr->name);
    printf("%d:", depth);
    indent(n);
    printf("  args:\n");
    printSyntaxTree(stFunCall_Args(t), n+4, depth+1);
    break;

  case Assg:
    printf("ASSG:\n");
    printf("%d:", depth);
    indent(n);
    printf("  Lhs:\n");
    printSyntaxTree(stAssg_Lhs(t), n+4, depth+1);
    printf("%d:", depth);
    indent(n);
    printf("  Rhs:\n");
    printSyntaxTree(stAssg_Rhs(t), n+4, depth+1);
    break;

  case Return:
    printf("RETURN:\n");
    printSyntaxTree(stReturn(t), n+2, depth+1);
    break;

  case For:
    printf("FOR\n");
    printf("%d:", depth);
    indent(n);
    printf("  init:\n");
    printSyntaxTree(stFor_Init(t), n+4, depth+1);
    printf("%d:", depth);
    indent(n);
    printf("  test:\n");
    printSyntaxTree(stFor_Test(t), n+4, depth+1);
    printf("%d:", depth);
    indent(n);
    printf("  update:\n");
    printSyntaxTree(stFor_Update(t), n+4, depth+1);
    printf("%d:", depth);
    indent(n);
    printf("  body:\n");
    printSyntaxTree(stFor_Body(t), n+4, depth+1);
    printf("%d:", depth);
    indent(n);
    printf("ENDFOR\n");
    break;

  case While:
    printf("WHILE\n");
    printSyntaxTree(stWhile_Test(t), n+4, depth+1);
    printf("%d:", depth);
    printf("  body:\n ");
    printSyntaxTree(stWhile_Body(t), n+4, depth+1);
    printf("%d:", depth);
    indent(n);
    printf("ENDWHILE\n");
    break;

  case If:
    printf("IF\n");
    printSyntaxTree(stIf_Test(t), n+4, depth+1);
    printf("%d:", depth);
    indent(n);
    printf("  then:\n");
    printSyntaxTree(stIf_Then(t), n+4, depth+1);
    printf("%d:", depth);
    indent(n);
    printf("  else:\n");
    printSyntaxTree(stIf_Else(t), n+4, depth+1);
    printf("%d:", depth);
    indent(n);
    printf("ENDIF\n");
    break;

  case STnodeList:  /* list of syntax tree nodes */
    printf("{\n");
    /* iterate down the list, printing out each tree in the list in turn */
    for (tntmp0 = t; tntmp0 != NULL; tntmp0 = stList_Rest(tntmp0)) {
      printSyntaxTree(stList_Head(tntmp0),n+2, depth+1);
    }
    printf("%d:", depth);
    indent(n);
    printf("}\n");
    break;

  default:
    fprintf(stderr, "Unknown syntax tree node type %d\n", t->ntype);
  }

  return;
}

/*
 * indent(n) -- insert n spaces.
 */
static void indent(int n)
{
  if (n < 0) return;

  while (n-- > 0) {
    putc(' ', stdout);
  }  
}

/*
 * printBinop(op) -- print out the syntax tree representation of a binary op
 */
static void printBinop(int op)
{
  switch (op) {
  case Plus:
    putc('+', stdout);
    break;
  case BinaryMinus:
    putc('-', stdout);
    break;
  case Mult:
    putc('*', stdout);
    break;
  case Div:
    putc('/', stdout);
    break;
  case Equals:
    printf("==");
    break;
  case Neq:
    printf("!=");
    break;
  case Leq:
    printf("<=");
    break;
  case Lt:
    putc('<', stdout);
    break;
  case Geq:
    printf(">=");
    break;
  case Gt:
    putc('>', stdout);
    break;
  case LogicalAnd:
    printf("&&");
    break;
  case LogicalOr:
    printf("||");
    break;
  }

  return;
}

/*
 * printUnop(op) -- print out the syntax tree representation of a unary op
 */
static void printUnop(int op)
{
  switch (op) {
  case UnaryMinus:
    putc('-', stdout);
    break;
    
  case LogicalNot:
    putc('!', stdout);
    break;
  }

  return;
}

static bool is_binop( SyntaxNodeType op )
{
  switch ( op ) {
  case Plus:
  case BinaryMinus:
  case Mult:
  case Div:
  case Equals:
  case Neq:
  case Leq:
  case Lt:
  case Geq:
  case Gt:
  case LogicalAnd:
  case LogicalOr:
    return true;
  default:
    return false;
  }
}

static void print_operands( TAC *tac )
{
  if ( tac->operand1 != NULL ) {
    switch (tac->operand1->atype) {
    case AT_Charcon:
      printf( "'%c' ", tac->operand1->val.iconst );
      break;
    case AT_Intcon:
      printf( "%d ", tac->operand1->val.iconst );
      break;
    case AT_StRef:
      if ( tac->operand1->val.stptr->type == t_Tmp_Addr ) { // array reference
	switch( tac->operand1->val.stptr->elt_type ) {
	case t_Char:
	  printf( "(%d)*%s(char) ", tac->operand1->val.stptr->varid, tac->operand1->val.stptr->name );
	  break;
	case t_Int:
	  printf( "(%d)*%s(int) ", tac->operand1->val.stptr->varid, tac->operand1->val.stptr->name );
	  break;
   	}
      } else {
	printf( "(%d)%s ", tac->operand1->val.stptr->varid, tac->operand1->val.stptr->name );
      }
      break;
    default:
      fprintf( stderr, "Invalid address type: %d for operand1!\n",
	       tac->operand1->atype);
      break;
    }
  }

  if ( is_binop(tac->optype) )
    printBinop( tac->optype );

  if ( tac->operand2 != NULL ) {
    switch (tac->operand2->atype) {
    case AT_Charcon:
      printf( "'%c' ", tac->operand2->val.iconst );
      break;
    case AT_Intcon:
      printf( " %d ", tac->operand2->val.iconst );
      break;
    case AT_StRef:
      if ( tac->operand2->val.stptr->type == t_Tmp_Addr ) { // array reference
	switch( tac->operand2->val.stptr->elt_type ) {
	case t_Char:
	  printf( " (%d)*%s(char) ", tac->operand2->val.stptr->varid, tac->operand2->val.stptr->name );
	  break;
	case t_Int:
	  printf( " (%d)*%s(int) ", tac->operand2->val.stptr->varid, tac->operand2->val.stptr->name );
	  break;
   	}
      } else {
	printf( " (%d)%s", tac->operand2->val.stptr->varid, tac->operand2->val.stptr->name );
      }
      break;
    default:
      fprintf( stderr, "Invalid address type: %d for operand2!\n",
	       tac->operand2->atype);
      break;
    }
  }
}

/**
 * Print out a single TAC instruction 'tac'.
 */
void printtac( TAC *tac )
{
  printf( "(%d)", tac->id );
  switch ( tac->optype ) {
  case Plus:
  case BinaryMinus:
  case Mult:
  case Div:
    printf( "\t(%d)%s = ", tac->dest->val.stptr->varid, tac->dest->val.stptr->name ); 
    print_operands( tac );
    break;
  case UnaryMinus:
    printf( "\t(%d)%s = -", tac->dest->val.stptr->varid, tac->dest->val.stptr->name );
    print_operands( tac );
    break;
  case Assg:
    if ( tac->dest->val.stptr->type == t_Tmp_Addr ) { // array reference
      switch( tac->dest->val.stptr->elt_type ) {
      case t_Char:
	printf( "\t(%d)*%s(char) = ", tac->dest->val.stptr->varid, tac->dest->val.stptr->name );
	break;
      case t_Int:
	printf( "\t(%d)*%s(int) = ", tac->dest->val.stptr->varid, tac->dest->val.stptr->name );
	break;
      }
    } else {
      printf( "\t(%d)%s = ", tac->dest->val.stptr->varid, tac->dest->val.stptr->name );
    }
      
    print_operands( tac );
    break;
  case Equals:
  case Neq:
  case Leq:
  case Lt:
  case Geq:
  case Gt:
  case LogicalAnd:
  case LogicalOr:
    printf( "\tif ( " ); 
    print_operands( tac );
    printf( " ) goto %s", tac->dest->val.label );
    break;
  case LogicalNot:
    printf( "\tif ( !" );
    print_operands( tac );
    printf( " ) goto %s", tac->dest->val.label );
    break;
  case Label: // label instruction
    printf( "%s:", tac->dest->val.label );
    break;
  case Goto: // goto instruction
    printf( "\tgoto %s", tac->dest->val.label );
    break;
  case Return:
    printf( "\tReturn " );
    print_operands( tac );
    break;
  case Param:
    printf( "\tParam " );
    print_operands( tac );
    break;
  case Call:
    printf( "\tCall " );
    print_operands( tac );
    break;
  case Retrieve:
    printf( "\tRetrieve " );
    print_operands( tac );
    break;
  case Enter:
    printf( "\tEnter(saved regs:0x%x) ", tac->dest->val.iconst );
    print_operands( tac );
    break;
  case Stringcon: // code for string constant, handled specially.
    printf( "\t%s = \"%s\"", tac->dest->val.stptr->name,
	    tac->dest->val.stptr->strcon );
    break;
  default:
    fprintf( stderr, "Invalid TAC opertion type: %d\n", tac->optype );
    break;
  }
}

/**
 * Print TAC sequence for the syntax tree node 't'.
 */
void print_TAC_seq( tnode *t, bool reverse )
{
  TAC *tac;

  if ( reverse == true ) {
    tac = t->tac_seq->end;
  } else {
    tac = t->tac_seq->start;
  }

  for (; tac != NULL;
       tac = (reverse == false)? tac->next : tac->prev) {
    printtac( tac );
    putchar( '\n' );
  }
}

/**
 * Print out the list of basic blocks for the current processed
 * function given the global header to its basic block list 'bhead'.
 */
void print_bbl()
{
  bbl *bbl_run = bhead;
  control_flow_list *cfl;

  while( bbl_run != NULL ) {
    printf( "BBL%d(# of TACs: %d, start: %s, end:",
	    bbl_run->bblnum, bbl_run->numtacs,
	    bbl_run->first_tac->dest->val.label );
    printtac( bbl_run->last_tac );
    printf( ", prev: BBL%d)\n", (bbl_run->prev != NULL) ? bbl_run->prev->bblnum : -1 );

    /* Print out successors. */
    printf( "     successors: ( " );
    cfl = bbl_run->succ;
    while ( cfl != NULL ) {
      printf( "BBL%d ", cfl->bb->bblnum );
      cfl = cfl->next;
    }
    printf( ")\n" );

    /* Print out predecessors. */
    printf( "     predecessors: ( " );
    cfl = bbl_run->pred;
    while ( cfl != NULL ) {
      printf( "BBL%d ", cfl->bb->bblnum );
      cfl = cfl->next;
    }
    printf( ")\n" );

    /* Print out bit vectors for reaching definitions. */
    if ( bbl_run->gen && bbl_run->kill &&
	 bbl_run->in && bbl_run->out ) {
      print_bv( "     Gen", bbl_run->gen, num_defuses-1 );
      print_bv( "     Kill", bbl_run->kill, num_defuses-1 );
      print_bv( "     In", bbl_run->in, num_defuses-1 );
      print_bv( "     Out", bbl_run->out, num_defuses-1 );
    }

    /* Print out bit vectors for liveness analysis. */
    if ( bbl_run->def && bbl_run->use ) {
      print_bv( "     Def", bbl_run->def, num_vars-1 );
      print_bv( "     Use", bbl_run->use, num_vars-1 );
      print_bv( "     In", bbl_run->livein, num_vars-1 );
      print_bv( "     Out", bbl_run->liveout, num_vars-1 );
      //      print_bv( "     Used", bbl_run->used, num_vars-1 );
    }

    bbl_run = bbl_run->next;
  }  
}
