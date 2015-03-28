/*
 * util.c -- assorted utilities
 *
 * Author: Saumya Debray
 */

#include "global.h"
#include "syntax-tree.h"

/*
 * return a pointer to a zero-initialized block of n bytes.
 */
void *zalloc(int n)
{
  void *ptr;

  if (n <= 0) {
    fprintf(stderr, "Illegal memory allocation size: %d\n", n);
    abort();
  }

  ptr = calloc(n, 1);

  if (ptr == NULL) {
    fprintf(stderr, "Not enough memory\n");
    abort();
  }

  return ptr;
}

/*
 * NewListNode(x, type, is_array) -- allocate a new linked list node 
 * and set its fields appropriately;
 */
llistptr NewListNode(char *str, int Type, bool arr)
{
  llistptr ltmp;

  ltmp = zalloc(sizeof(*ltmp));
  ltmp->name = str;
  ltmp->type = Type;
  ltmp->is_array = arr;

  return ltmp;
}

/*
 * Attach(list1, list2) -- given two linked lists, attaches the second 
 * at the end of the first.
 */
llistptr Attach(llistptr list1, llistptr list2)
{
  llistptr ltmp;

  if (list1 == NULL) return list2;
  /*
   * find the last element of the list.
   */
  for (ltmp = list1; ltmp != NULL && ltmp->next != NULL; ltmp = ltmp->next) {
  }
  
  ltmp->next = list2;

  return list1;
}

/**
 * Check whether the given 'optype' is a arithmetic operation.
 */
bool is_arith_op( SyntaxNodeType optype )
{
  switch ( optype ) {
  case Plus:
  case BinaryMinus:
  case UnaryMinus:
  case Mult:
  case Div:
    return true;
  default:
    return false;
  }
}

/**
 * Check whether the given 'optype' is a relational operation.
 */
bool is_relational_op( SyntaxNodeType optype )
{
  switch ( optype ) {
  case Equals:
  case Neq:
  case Leq:
  case Lt:
  case Geq:
  case Gt:
    return true;
  default:
    return false;
  }
}

/**
 * Check if address 'var' is a valid local variable, either
 * user defined or compiler generated tmp variables.
 */
bool is_valid_local( address *var )
{
  if ( var != NULL &&
       var->atype == AT_StRef &&
       var->val.stptr->scope == Local ) {
    if ( var->val.stptr->type == t_Int ||
	 var->val.stptr->type == t_Char ||
	 var->val.stptr->type == t_Tmp_Var ) {
      return true;
    }
  }
  return false;
}

