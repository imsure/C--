/*
 * symbol-table.c
 *
 * Author: Saumya Debray
 */

#include <assert.h>
#include "global.h"
#include "symbol-table.h"

extern int CurrScope, CurrType, fnRetType;
extern char *fnName;
extern llistptr lptr;
extern bool is_extern;
extern symtabnode *currFun;

int tmpvar_counter = 0; // counter for the tmp variables
                        // (exclude those holding array addresses).
int tmpaddr_counter = 0; // counter for the tmp variables holding array addresses
int tmpstr_counter = 0; // counter for the tmp variables holding a string constant

#define TMP_VAR_PREFIX "_tvar"
#define TMP_ADDR_PREFIX "_taddr"
#define TMP_STR_PREFIX "_tstr"

#define HASHTBLSZ 256

static symtabnode *SymTab[2][HASHTBLSZ];

static int hash(char *str)
{
  int n = 0;

  for ( ; str != NULL && *str != '\0'; str++) {
    n += *str;
  }

  return n % HASHTBLSZ;
}

/*
 * SymTabInit(sc)
 *
 * Given a scope sc, initialize the symbol table for that scope by setting
 * all the hash table buckets to NULL.
 */
void SymTabInit(int sc)
{
  int i;

  for (i = 0; i < HASHTBLSZ; i++) {
    SymTab[sc][i] = NULL;
  }
}

/*
 * SymTabLookup(str, sc)
 *
 * Look up the string str in the symbol table with scope sc.  If found,
 * return a pointer to the corresponding symbol table node, otherwise
 * return NULL.
 */
symtabnode *SymTabLookup(char *str, int sc)
{
  int hval;
  symtabnode *stptr;

  assert(str);

  hval = hash(str);

  for (stptr = SymTab[sc][hval]; stptr != NULL; stptr = stptr->next) {
    if (strcmp(str, stptr->name) == 0) {
      return stptr;
    }
  }

  return NULL;
}

/*
 * SymTabLookupAll(str)
 *
 * Look up the string str in the symbol table, starting with the
 * local symbol table and then (if not found) in the global table.
 * If found in either table, return a pointer to the corresponding
 * symbol table node, otherwise return NULL.
 */
symtabnode *SymTabLookupAll(char *str)
{
  symtabnode *stptr;

  assert(str);

  stptr = SymTabLookup(str, Local);

  if (stptr == NULL) {
    stptr = SymTabLookup(str, Global);
  }

  return stptr;
}

/*
 * SymTabInsert(str, sc)
 *
 * Add string str to the symbol table with scope sc, and return a
 * pointer to the resulting entry.  This code assumes that str does not
 * already occur in that symbol table; it gives an error message if it does.
 */
symtabnode *SymTabInsert(char *str, int sc)
{
  int hval;
  symtabnode *sptr;
  
  assert(str != 0);

  sptr = SymTabLookup(str, sc);
  CASSERT(sptr == NULL, ("multiple declarations of %s", str));

  if (sptr != NULL) return sptr;

  hval = hash(str);
  
  sptr = (symtabnode *) zalloc(sizeof(symtabnode));
  sptr->name = str;
  sptr->scope = sc;
  
  sptr->next = SymTab[sc][hval];
  SymTab[sc][hval] = sptr;
  
  return sptr;
}

/*
 * SymTabRecordFunInfo(isProto) -- records information in the symbol
 * table about a function.  The argument isProto indicates whether or
 * not this is a prototype.  It communicates with the YACC parser
 * through the globals fnName (the name of the function), fnRetType
 * (the return type), and lptr (a linked list of information about the
 * parameters).  It returns a pointer to the symbol table record of
 * the function.
 */
symtabnode *SymTabRecordFunInfo(bool isProto) 
{
  symtabnode *stptr, *func;
  llistptr ltmp;
  symtabnode *formal_list_hd, *formal_list_tl, *formal;
  int n;

  func = SymTabLookup(fnName, Global);
  /*
   * It's only OK to have an entry for this ID in the symbol table already
   * if the previous entry was the prototype and this is the actual
   * definition.
   */
  if (func != NULL) {
    if (func->fn_proto_state == FN_PROTO && !isProto) {
      /* 
       * the previous definition was a prototype, and this is the
       * real definition.  Check and make sure that the type info
       * in the prototype matches that for the definition.
       */
      formal = func->formals;
      ltmp = lptr;
      n = 1;
      while (formal != NULL && ltmp != NULL) {
	if ((formal->elt_type == t_None 
	     && !ltmp->is_array 
	     && formal->type != ltmp->type)  // neither is an array
	    || (formal->elt_type != t_None && !ltmp->is_array) // formal is array, but not ltmp
	    || (formal->elt_type == t_None && ltmp->is_array)  // ltmp is array, but not formal
	    || (formal->elt_type != t_None
		&& ltmp->is_array
		&& formal->elt_type != ltmp->type /* both are arrays */)) {
	  errmsg("function %s: type of argument %d does not match that of prototype",
		 fnName, n);
	}
	n++;
	formal = formal->next;
	ltmp = ltmp->next;
      }
      if (!(formal == NULL && ltmp == NULL)) {
	errmsg("function %s: no of arguments in definition does not match prototype",
	       fnName);
      }
      if (fnRetType != func->ret_type) {
	errmsg("function %s: return type does not match that of prototype", fnName);
      }
      if (func->is_extern) {
	errmsg("function %s was previously defined as EXTERN", fnName);
      }
    }
    else {
      errmsg("Multiple prototypes/definitions for function %s", fnName);
    }
  }
  else {
    func = SymTabInsert(fnName, Global);
  }

  func->type = t_Func;
  func->ret_type = fnRetType;

  formal_list_hd = formal_list_tl = NULL;

  for (ltmp = lptr; ltmp != NULL; ltmp = ltmp->next) {
    if (CurrType == t_None) {
      errmsg("Illegal type [void] for identifier %s", lptr->name);
    }
    else {
      stptr = SymTabInsert(ltmp->name, CurrScope);
      stptr->formal = true;
      if (ltmp->is_array) {
	stptr->type = t_Array;
	stptr->elt_type = ltmp->type;
      }
      else {
	stptr->type = ltmp->type;
	stptr->elt_type = t_None;
      }
      /*
       * Now create a record for the list of formals, and copy over
       * info from stptr.
       */
      formal = zalloc(sizeof(*formal));
      formal->name =     stptr->name;
      formal->scope =    stptr->scope;
      formal->formal =   stptr->formal;
      formal->type =     stptr->type;
      formal->elt_type = stptr->elt_type;

      if (formal_list_hd == NULL) {
	formal_list_hd = formal_list_tl = formal;
      }
      else {
	formal_list_tl->next = formal;
	formal_list_tl = formal;
      }
    }
  } /* for */

  func->formals = formal_list_hd;

  if (isProto && func->fn_proto_state != FN_DEFINED) {
    func->fn_proto_state = FN_PROTO;
  }
  else {
    func->fn_proto_state = FN_DEFINED;
  }

  func->is_extern = is_extern;
  fnName = NULL;

  return func;
}

/**
 * Create a new or return an unused tmp variable for holding
 * intermediate computed value.
 * It returns the symbol table entry to the tmp variable.
 *
 * Note that this function only applies tmp variable stored in the
 * local symbol table that does not represent an array address. For tmp
 * variable holding an array address, use newtmp_addr().
 */
symtabnode *newtmp_var()
{
  int hval;
  char *name;
  symtabnode *sptr;
  int sc = Local;

  /* name for the tmp variable */
  name = (char *) zalloc( 10 );
  sprintf( name, "%s%d", TMP_VAR_PREFIX, tmpvar_counter++ );

  /* Check if tmp variable 'name' already exists */
  sptr = SymTabLookup(name, sc);

  if (sptr != NULL) {
    return sptr; // reuse it
  } else { // create a new tmp
    hval = hash(name);
  
    sptr = (symtabnode *) zalloc(sizeof(symtabnode));
    sptr->name = name;
    sptr->scope = sc;
    sptr->type = t_Tmp_Var;
  
    sptr->next = SymTab[sc][hval];
    SymTab[sc][hval] = sptr;

    return sptr;
  }
}

/**
 * Create a new tmp variable for holding an array address.
 * It returns the symbol table entry to the tmp variable.
 */
symtabnode *newtmp_addr()
{
  int hval;
  char *name;
  symtabnode *sptr;
  int sc = Local;

  /* name for the tmp variable */
  name = (char *) zalloc( 10 );
  sprintf( name, "%s%d", TMP_ADDR_PREFIX, tmpaddr_counter++ );

  /* Check if tmp variable 'name' already exists */
  sptr = SymTabLookup(name, sc);

  if (sptr != NULL) {
    return sptr; 
  } else { // create a new tmp
    hval = hash(name);
  
    sptr = (symtabnode *) zalloc(sizeof(symtabnode));
    sptr->name = name;
    sptr->scope = sc;
    sptr->type = t_Tmp_Addr;
  
    sptr->next = SymTab[sc][hval];
    SymTab[sc][hval] = sptr;

    return sptr;
  }
}

/**
 * Create a global symbol table entry for a string constant.
 */
symtabnode *newtmp_strcon( const char *str )
{
  int hval;
  char *name;
  symtabnode *sptr;
  int sc = Global;

  name = (char *) zalloc( 5 );
  sprintf( name, "%s%d", TMP_STR_PREFIX, tmpstr_counter++ );

  sptr = SymTabLookup(name, sc);
  CASSERT(sptr == NULL, ("multiple declarations of %s", name));

  if (sptr != NULL) return sptr;

  hval = hash(name);
  
  sptr = (symtabnode *) zalloc(sizeof(symtabnode));
  sptr->name = name;
  sptr->scope = sc;
  sptr->type = t_Tmp_Str;
  sptr->strcon = (char *) zalloc( strlen(str) + 1 );
  sprintf( sptr->strcon, "%s", str );
  
  sptr->next = SymTab[sc][hval];
  SymTab[sc][hval] = sptr;
  
  return sptr;
}

/**
 * Map global data into mips data section.
 */
void output_mips_data_section()
{
  int i;
  symtabnode *stptr;

  printf("\t.data\n");

  for (i = 0; i < HASHTBLSZ; i++) {
    for (stptr = SymTab[Global][i]; stptr != NULL; stptr = stptr->next) {
      if ( stptr->type == t_Tmp_Str && stptr->to_mips != true ) {
	printf( "%s:\t.asciiz \"%s\"\n", stptr->name, stptr->strcon );
	printf( "\t.align 2\n" );
	stptr->to_mips = true;
	continue;
      }
      if ( stptr->type == t_Int && stptr->to_mips != true ) {
	printf( "%s:\t.space %d\n", stptr->name, INT_SZ );
	stptr->to_mips = true;
	continue;
      }
      if ( stptr->type == t_Char && stptr->to_mips != true ) {
	printf( "%s:\t.space %d\n", stptr->name, CHAR_SZ );
	printf( "\t.align 2\n" );
	stptr->to_mips = true;
	continue;
      }
      if ( stptr->type == t_Array && stptr->to_mips != true ) {
	switch(stptr->elt_type) {
	case t_Char:
	  printf("%s:\t.space %d\n", stptr->name, stptr->num_elts * CHAR_SZ);
	  printf( "\t.align 2\n" );
	  break;
	case t_Int:
	  printf("%s:\t.space %d\n", stptr->name, stptr->num_elts * INT_SZ);
	  break;
	}
	stptr->to_mips = true;
	continue;
      }
    }
  }
}

/*
 * CleanupFnInfo() -- clean up after processing information
 * for a function prototype/definition.
 */
void CleanupFnInfo(void)
{
  fnName = NULL;
  lptr = NULL;
  currFun = NULL;
  is_extern = false;
  CurrScope = Global;
#if 0
  DumpSymTab(); 
#endif
  SymTabInit(Local);
}

/*********************************************************************
 *                                                                   *
 *                           for debugging                           *
 *                                                                   *
 *********************************************************************/

void printType(symtabnode *stptr)
{
  symtabnode *formals;
  switch (stptr->type) {
  case t_Char: 
    printf("C(offset2fp=%d)", stptr->offset2fp);
    CASSERT(stptr->elt_type == t_None, ("<?!>"));
    break;
  case t_Int:  printf("I(offset2fp=%d)", stptr->offset2fp);
    CASSERT(stptr->elt_type == t_None, ("<?!>"));
    break;
  case t_Array:
    switch(stptr->elt_type) {
    case t_Char: printf("C[%d](offset2fp=%d)", stptr->num_elts, stptr->offset2fp); break;
    case t_Int: printf("I[%d](offset2fp=%d)", stptr->num_elts, stptr->offset2fp); break;
    default: printf("%d?[%d]", stptr->elt_type, stptr->num_elts);
    }
    break;
  case t_Func:
    printf("(");
    if (stptr->formals == NULL) {
      printf("void");
    }
    else {
      for (formals = stptr->formals; formals; formals = formals->next) {
	printType(formals);
	if (formals->next) {
	  printf(", ");
	}
      }
    }
    printf(") -> ");
    switch (stptr->ret_type) {
    case t_Char: printf("C"); break;
    case t_Int: printf("I"); break;
    case t_None: printf("void"); break;
    default: printf("??%d", stptr->ret_type);
    }
    break;
  case t_Tmp_Var:
    printf("Tmp_Var(offset2fp=%d)", stptr->offset2fp);
    break;
  case t_Tmp_Addr:
    printf("Tmp_Addr(offset2fp=%d)", stptr->offset2fp);
    break;
  case t_None:
    printf("-");
    break;
  default: printf("?!?%d", stptr->type);
  }
}

void printSTNode(symtabnode *stptr)
{
  printf(">> %s: scope = %c%s; type: ",
	 stptr->name,
	 (stptr->scope == Global ? 'G' : 'L'),
	 (stptr->formal == true ? "<formal param>" : ""));
  printType(stptr);
  printf("\n");
}

/**
 * Compute offset to $fp for each actual parameters to
 * be passed to the function whose symbol table entry is 'func'.
 *
 * Since we are passing parameters from left to right:
 *
 * param a_1
 * param a_2
 * ...
 * param a_n
 *
 * So a1 would appear farest to the $fp for callee, and an would be
 * the cloest to $fp among all parameters. So the offset for a_n is 1
 * and offset for a_1 is n.
 */
void offset2fp_formals( symtabnode *func )
{
  int i, num_formals = 0;
  symtabnode *formal, *stptr;
  
  formal = func->formals; // a list of formals for the function.

  while ( formal != NULL ) {
    ++num_formals;
    formal = formal->next;
  }
  formal = func->formals; // reset pointer

  while ( formal != NULL ) {
    formal->offset2fp = num_formals--;
    for (i = 0; i < HASHTBLSZ; i++) {
      for (stptr = SymTab[Local][i]; stptr != NULL; stptr = stptr->next) {
	if ( stptr->formal && strcmp(stptr->name, formal->name) == 0 ) { 
	  stptr->offset2fp = formal->offset2fp;
	}
      }
    }
    
    formal = formal->next;
  }
}

/**
 * Compute offset to $fp for local variables/tmps.
 * It returns the offset of the last local variable, which is also
 * the stack size to be allocated.
 */
int offset2fp_locals()
{
  int i, offset = 0, num_chars;
  symtabnode *stptr;

  for (i = 0; i < HASHTBLSZ; i++) {
    for (stptr = SymTab[Local][i]; stptr != NULL; stptr = stptr->next) {
      if ( stptr->formal ) { // ignore formals
	continue;
      }
      switch (stptr->type) {
      case t_Char:
	offset += 4; // enforce 4 bytes alignment
	stptr->offset2fp = offset;
	break;
      case t_Tmp_Var:
      case t_Tmp_Addr:
      case t_Int:
	offset += 4;
	stptr->offset2fp = offset;
	break;
      case t_Array:
	switch(stptr->elt_type) {
	case t_Char:
	  num_chars = stptr->num_elts;
	  /* make sure 4 bytes alignment */
	  switch ( num_chars % 4 ) {
	  case 0: break;
	  case 1: num_chars += 3; break;
	  case 2: num_chars += 2; break;
	  case 3: num_chars += 1; break;
	  }
	  offset += num_chars;
	  stptr->offset2fp = offset;
	  break;
	case t_Int:
	  offset += stptr->num_elts * 4;
	  stptr->offset2fp = offset;
	  break;
	default: printf("%d?[%d]", stptr->elt_type, stptr->num_elts);
	}
	break;
      }
    }
  }
  
  return offset;
}

void DumpSymTabLocal()
{
  int i;
  symtabnode *stptr;

  printf("-------------------- LOCAL SYMBOL TABLE --------------------\n");

  for (i = 0; i < HASHTBLSZ; i++) {
    for (stptr = SymTab[Local][i]; stptr != NULL; stptr = stptr->next) {
      printSTNode(stptr);
    }
  }

  printf("------------------------------------------------------------\n");

}

void DumpSymTabGlobal()
{
  int i;
  symtabnode *stptr;

  printf("-------------------- GLOBAL SYMBOL TABLE --------------------\n");

  for (i = 0; i < HASHTBLSZ; i++) {
    for (stptr = SymTab[Global][i]; stptr != NULL; stptr = stptr->next) {
      printSTNode(stptr);
    }
  }

  printf("------------------------------------------------------------\n");

}

void DumpSymTab()
{
  DumpSymTabGlobal();
  DumpSymTabLocal();
}

/*********************************************************************/
