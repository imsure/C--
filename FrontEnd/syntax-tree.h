/*
 * syntax-tree.h
 *
 * Author: Saumya Debray
 */

#ifndef _SYNTAX_TREE_H_
#define _SYNTAX_TREE_H_

#include "symbol-table.h"

/**
 * type for syntax tree node.
 * Note that we are reusing this enum for TAC operation type, so
 * only commented fields are valid TAC operation types. And those
 * TAC operation types appended after STnodeList are also not
 * valid syntax tree node type.
 */
typedef enum SyntaxNodeType {
  Error,
  Intcon, 
  Charcon, 
  Stringcon, // operation type of three address code (for string constant only)
  Var,
  ArraySubscript,
  Plus, // operation type of three address code
  UnaryMinus, // operation type of three address code
  BinaryMinus, // operation type of three address code
  Mult, // operation type of three address code
  Div, // operation type of three address code
  Equals, // operation type of three address code
  Neq, // operation type of three address code
  Leq, // operation type of three address code
  Lt, // operation type of three address code
  Geq, // operation type of three address code
  Gt, // operation type of three address code
  LogicalAnd,
  LogicalOr,
  LogicalNot, 
  FunCall,
  Assg, // operation type of three address code
  Return, // operation type of three address code
  For,
  While,
  If,
  STnodeList,
  Goto, // operation type of three address code
  Label, // operation type of three address code
  Param, // operation type of three address code
  Call, // operation type of three address code
  Retrieve, // operation type of three address code
  Enter, //  operation type of three address code
  Noop // added for operation type of three address code
} SyntaxNodeType;

/**
 * Type of address for TAC.
 */
typedef enum addrtype {
  AT_Intcon, // integer constant
  AT_Charcon, // char constant
  AT_Stringcon, // string constant
  AT_StRef, // symbol table reference
  AT_Label, // label
  AT_Noop // no operation, for int and char variables only
} addrtype;

/**
 * A list of local varibles/tmps with their live ranges identified.
 * This will be used for register allocation.
 */
typedef struct localvars {
  symtabnode *stptr;
  struct localvars *next;
} localvars;

/**
 * Represents an address in TAC (three address code).
 */
typedef struct address {
  enum addrtype atype; // type of the address
  union {
    int iconst; // integer constant value if the
                // address is a char or int constant.
    char *label; // name of the label if the address is a label
                      // can be either a compiler generated label or a function name.
    symtabnode *stptr; // symbol table entry if the address is a variable(local, tmp, global)
  } val;
} address;

/**
 * Represents a single TAC instruction.
 */
typedef struct three_address_code {
  SyntaxNodeType optype; // type of operation
  struct address *dest, *operand1, *operand2; // three addresses
  struct three_address_code *prev; // previous instruction
  struct three_address_code *next; // next instruction
  int id; // a unique positive number if TAC is a definition
          // to some local variables/tmps or it reads some local
          // variables/tmps. It is used for computing reaching definitions.
  bool is_dead; // indicate if TAC is dead.
} TAC;

/**
 * Represents a sequence of TAC from 'start' to 'end'.
 */
typedef struct TAC_sequence {
  struct three_address_code *start;
  struct three_address_code *end;
} TAC_seq;


struct stref {  // symbol table reference: subscripted expr or function call
  symtabnode *stptr;
  struct treenode *exp;
};

struct expr {  // unary and binary expressions, and expression lists
  struct treenode *lchild, *rchild;
};

struct stmt {  // statements
  struct treenode *child0, *child1, *child2, *child3;
};

typedef struct treenode {
  enum SyntaxNodeType ntype;   // the node type for a syntax tree node
  int etype;  // the type of the value of a syntax tree node, once that
              // node has been evaluated.  For nodes that don't have a
              // value, e.g., statements, this is set to t_None.
  union {
    int iconst;
    char *strconst;
    struct stref strefNode;
    struct expr exprNode;
    struct stmt stmtNode;
  } val;

  symtabnode *place; // symbol table location where the value of the expression
                     // will be kept at runtime.
  TAC_seq *tac_seq; // sequence of TAC for the syntax tree node.
} tnode, *tnptr;

tnode *mkConstNode(SyntaxNodeType ntype, int etype, int n);
tnode *mkStrNode(char *s);
tnode *mkSymTabRefNode(SyntaxNodeType ntype, int etype, symtabnode *stptr, tnode *t0);
tnode *mkExprNode(SyntaxNodeType ntype, int etype, tnode *e1, tnode *e2);
tnode *mkSTNode(SyntaxNodeType ntype, int etype, tnode *x0, tnode *x1, tnode *x2, tnode *x3);
tnode *mkErrorNode(void);
tnode *mkListNode(tnode *hd, tnode *tl);
tnode *AppendReturn(tnode *t);

bool ActualsMatchFormals(symtabnode *fn, tnode *actuals);
tnode *SynTreeUnExp(SyntaxNodeType ntype, tnode *e1);
tnode *SynTreeBinExp(SyntaxNodeType ntype, tnode *e1, tnode *e2);

#define ConstVal(x)   (x)->val.iconst
#define StrVal(x)     (x)->val.strconst

#define SymTabPtr(x)  (x)->val.strefNode.stptr
#define ExprPtr(x)    (x)->val.strefNode.exp

#define LChild(x)     (x)->val.exprNode.lchild
#define RChild(x)     (x)->val.exprNode.rchild

#define Child0(x)     (x)->val.stmtNode.child0
#define Child1(x)     (x)->val.stmtNode.child1
#define Child2(x)     (x)->val.stmtNode.child2
#define Child3(x)     (x)->val.stmtNode.child3

#define ListNode(x)  (x)->val.exprNode.lchild
#define ListNext(x)  (x)->val.exprNode.rchild

#endif /* _SYNTAX_TREE_H_ */
