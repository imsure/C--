/*
 * symbol-table.h
 *
 * Author: Saumya Debray
 */

#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include "global.h"

#define Global 0
#define Local  1

/**
 * A linked list of live ranges.
 */
typedef struct live_range {
  bitvec *val;
  struct live_range *next;
} live_range;

struct colive_list;

typedef struct stblnode {
  char *name;
  char *strcon; // string constant value, on used when type==t_Tmp_Str
  int scope;
  bool formal;             /* true if formal, false o/2 */
  int type;                /* the type of the symbol */
  int elt_type;            /* the type of array elements */
  int num_elts;            /* no. of array elements */
  int ret_type;            /* the return type of a function */
  struct stblnode *formals;  /* the list of formals for a function */
  int fn_proto_state;      /* status of prototype definitions for a function */
  bool is_extern;          /* whether or not an ID was declared as an extern */
  struct stblnode *next;
  int offset2fp; // offset to frame pointer, only applies to local variables and tmps (type=t_Tmp_Var).
  bool to_mips; // indicate whether the global variables or tmps (type=t_Tmp_Strcon) has been
                // converted to MIPS .data section.
  bitvec *bv; // bit vector for holding the set of instructions that defines the variable.
              // This is for reaching definition.
  int varid; // a unique id for the local variable. This is for intra-procedural liveness analysis.
  live_range *live_ranges; // a list of live ranges for the variable
  bitvec *single_lr; // the single live range for the variable
  struct colive_list *colives; // the list of varibles that co-live with the symbol.
  int degree;
  bool removed;
  int regnum;
  bool is_loaded;
  bool is_dirty;
} symtabnode;

typedef struct colive_list {
  symtabnode *stptr;
  bool tmp_removed;
  bool perm_removed;
  struct colive_list *next;
} colive_list;

/*********************************************************************
 *                                                                   *
 *                             Prototypes                            *
 *                                                                   *
 *********************************************************************/

void SymTabInit(int sc); // initialize the symbol table at scope sc to empty
symtabnode *SymTabLookup(char *str, int sc); // lookup scope sc
symtabnode *SymTabLookupAll(char *str); // lookup local first, then global
symtabnode *SymTabInsert(char *str, int sc);  // add ident to symbol table
symtabnode *SymTabRecordFunInfo(bool isProto);
void CleanupFnInfo(void);
/*
 * Defugging functions
 */
void printSTNode(symtabnode *stptr);
void DumpSymTabLocal();
void DumpSymTabGlobal();
void DumpSymTab();

/*********************************************************************
 *                                                                   *
 *          Functions: states for prototypes and definitions         *
 *                                                                   *
 *********************************************************************/

#define FN_PROTO     0  // prototype seen
#define FN_DEFINED   1  // definition seen

#endif /* _SYMBOL_TABLE_H_ */
