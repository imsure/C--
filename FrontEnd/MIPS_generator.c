/**
 * Generate MIPS assembly code from TAC.
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

/* General purpose MIPS registers */
#define REG_8 8
#define REG_9 9
#define REG_10 10

#define REG_V0 2 // register for holding return value

/**
 * Spim routinue for printing int value.
 */
void spim_print_int()
{
  printf( "\t.text\n" );
  printf( "print_int:\n" );

  printf( "\tli $v0, 1\n" );  
  printf( "\tlw $a0, 0($sp)\n" );
  printf( "\tsyscall\n" );

  printf( "\tjr $ra\n\n" );
}

/**
 * Spim routinue for printing string constant.
 */
void spim_print_string()
{
  printf( "\t.text\n" );
  printf( "print_string:\n" );

  printf( "\tli $v0, 4\n" );  
  printf( "\tlw $a0, 0($sp)\n" );
  printf( "\tsyscall\n" );

  printf( "\tjr $ra\n\n" );
}

/**
 * Load the value of the global variable pointed by symbol table
 * entry 'stptr' to the register $(reg_num).
 */
static void load_global_var_to_reg( symtabnode *stptr, int reg_num )
{
  /* Check each possible target this symbol table entry could point to. */
  switch ( stptr->type ) {
  case t_Int: // global int
    printf( "\tlw $%d, _%s # Load global int %s.\n",
	    reg_num, stptr->name, stptr->name );
    break;
  case t_Char: // global char
    printf( "\tlb $%d, _%s # Load global char %s.\n",
	    reg_num, stptr->name, stptr->name );
    break;
  case t_Array: // global array ( its address )
    if ( stptr->elt_type == t_Int ) {
      printf( "\tla $%d, _%s # Load address of global int array %s.\n",
	      reg_num, stptr->name, stptr->name );
    } else {
      printf( "\tla $%d, _%s # Load address of global char array %s.\n",
	      reg_num, stptr->name, stptr->name );
    }
    break;
  case t_Tmp_Str: // string constant
    printf( "\tla $%d, _%s # Load string const address %s.\n",
	    reg_num, stptr->name, stptr->name );
    break;
  default: // other types are not valid!
    fprintf( stderr,
	     "Symbol table entry type(%d) is invalid for a global variable as an operand!\n",
	     stptr->type );
    exit( -1 );
    break;
  }   
}

/**
 * Load the value of the local/tmp variable pointed by symbol table
 * entry 'stptr' to the register $(reg_num).
 */
static void load_local_var_to_reg( symtabnode *stptr, int reg_num )
{
  switch ( stptr->type ) {
  case t_Int: // local int variable
    printf( "\tlw $%d, -%d($fp) # Load local int %s.\n",
	    reg_num, stptr->offset2fp, stptr->name );
    break;
  case t_Char: // local char variable
    printf( "\tlb $%d, -%d($fp) # Load local char %s.\n",
	    reg_num, stptr->offset2fp, stptr->name );
    break;
  case t_Array: // local array variable
    if ( stptr->elt_type == t_Int ) {
      printf( "\tla $%d, -%d($fp) # Load address of local int array %s.\n",
	      reg_num, stptr->offset2fp, stptr->name );
    } else {
      printf( "\tla $%d, -%d($fp) # Load address of local char array %s.\n",
	      reg_num, stptr->offset2fp, stptr->name );
    }
    break;
  case t_Tmp_Var: // local tmp variable
    printf( "\tlw $%d, -%d($fp) # Load tmp variable %s.\n",
	    reg_num, stptr->offset2fp, stptr->name );
    break;
  case t_Tmp_Addr: // local tmp address (reference to an array element)
    /* Load address into $(reg_num+1) first. */
    printf( "\tlw $%d, -%d($fp) # Load tmp address %s.\n",
	    reg_num+1, stptr->offset2fp, stptr->name );
    /* Load value of array element referenced by the address stored in $(reg_num+1). */
    if ( stptr->elt_type == t_Int ) {
      printf( "\tlw $%d, ($%d) # Load value of the int array element pointed by %s.\n",
	      reg_num, reg_num+1, stptr->name );
    } else {
      printf( "\tlb $%d, ($%d) # Load value of the char array element pointed by %s.\n",
	      reg_num, reg_num+1, stptr->name );
    }
    break;
  default:
    fprintf( stderr,
	     "Symbol table entry type(%d) is invalid for a local variable as an operand!\n",
	     stptr->type );
    exit( -1 );
    break;
  }  
}

/**
 * Load the value of the formal parameter pointed by symbol table
 * entry 'stptr' to the register $(reg_num).
 *
 * Note that we skip the case where the formal is a reference to a string constant.
 */
static void load_formal_to_reg( symtabnode *stptr, int reg_num )
{
  switch ( stptr->type ) {
  case t_Int: // formal is a int value
    printf( "\tlw $%d, %d($fp) # Load int formal %s.\n",
	    reg_num, 4*stptr->offset2fp + 4, stptr->name );
    break;
  case t_Char: // formal is a char value
    printf( "\tlb $%d, %d($fp) # Load char formal %s.\n",
	    reg_num, 4*stptr->offset2fp + 4, stptr->name );
    break;
  case t_Array: // formal is an array reference
    if ( stptr->elt_type == t_Int ) { // the address is pushed on stack,
      // so do not use la !
      printf( "\tlw $%d, %d($fp) # Load address of formal int array %s.\n",
	      reg_num, 4*stptr->offset2fp + 4, stptr->name );
    } else {
      printf( "\tlw $%d, %d($fp) # Load address of formal char array %s.\n",
	      reg_num, 4*stptr->offset2fp + 4, stptr->name );
    }
    break;
  default:
    fprintf( stderr,
	     "Symbol table entry type(%d) is invalid for a formal parameter as an operand!\n",
	     stptr->type );
    exit( -1 );
    break;
  }
}

/**
 * Load the value of 'operand' into register $reg_num.
 * 'operand' is an address in the context of TAC, not a memory address.
 */
static void load_operand_to_reg( address *operand, int reg_num )
{
  symtabnode *stptr;

  /* A speical case where an operand is a constant except assigning
     a constant a tmp variable which is handled in tac2mips_assg().
     This is when we calculate the offset of an array element:
     "_tvar0 = i * 4" for A[i]. */
  /* Update: the above comment is not valid any more because
     after copy propagation optimization, both int or char constant
     could appear in operand1 or operand2. So adjust to handle this. */
  if ( operand->atype == AT_Intcon || operand->atype == AT_Charcon ) {
    switch ( operand->atype ) {
    case AT_Charcon: // char constant
      printf( "\tli $%d, %d # Load char constant.\n",
	      reg_num, operand->val.iconst );
      break;
    case AT_Intcon: // int constant
      if ( operand->val.iconst < MAX_16bits ) { // small int constant
	printf( "\tli $%d, %d # Load int constant shorter than 16-bits\n",
		reg_num, operand->val.iconst );
      } else { // large int constant
	printf( "\tlui $%d, %d # Load higher 16-bits\n",
		reg_num, operand->val.iconst >> 16 );
	printf( "\tori $%d, %d # Load lower 16-bits\n",
		reg_num, operand->val.iconst & 0xffff );
      }
      break;
    default: break;
    }
    return; // do not continue
  }

  /* For operand appeared in arithmetic operations, it must be
     a symbol table entry. */
  stptr = operand->val.stptr;
  if ( stptr->scope == Global ) { // global variable
    load_global_var_to_reg( stptr, reg_num );
  } else { // local scope
    if ( stptr->formal == true ) { // formal parameters
      load_formal_to_reg( stptr, reg_num );
    } else { // local/tmp variable
      load_local_var_to_reg( stptr, reg_num );
    }
  }
}

/**
 * Store the value in the register $(reg_num) to global variable
 * pointed by symbol table entry 'stptr'.
 *
 * When used as a destination, the global variable can only be
 * either int or char. Global array element will be turned into
 * *t_Tmp_Addr, so does not count.
 */
static void store_value_to_global( symtabnode *stptr, int reg_num )
{
  /* Check each possible target this symbol table entry could point to. */
  switch ( stptr->type ) {
  case t_Int: // global int
    printf( "\tsw $%d, _%s # Store to global int %s.\n",
	    reg_num, stptr->name, stptr->name );
    break;
  case t_Char: // global char
    printf( "\tsb $%d, _%s # Store to global char %s.\n",
	    reg_num, stptr->name, stptr->name );
    break;
  default:
    fprintf( stderr,
	     "Symbol table entry type(%d) is invalid for a global variable as an dest!\n",
	     stptr->type );
    exit( -1 );
    break;
  }
}

/**
 * Store the value the register $(reg_num) to the formal parameter
 * pointed by symbol table entry 'stptr'.
 *
 * This is only valid when formal is a int or char variable.
 */
static void store_value_to_formal( symtabnode *stptr, int reg_num )
{
  switch ( stptr->type ) {
  case t_Int: // formal is a int
    printf( "\tsw $%d, %d($fp) # Store to int formal %s.\n",
	    reg_num, 4*stptr->offset2fp + 4, stptr->name );
    break;
  case t_Char: // formal is a char
    printf( "\tsb $%d, %d($fp) # Store to char formal %s.\n",
	    reg_num, 4*stptr->offset2fp + 4, stptr->name );
    break;
  default:
    fprintf( stderr,
	     "Symbol table entry type(%d) is invalid for a formal parameter as a dest!\n",
	     stptr->type );
    exit( -1 );
    break;
  }
}

/**
 * Store the value in the register $(reg_num) to local/tmp variable
 * pointed by symbol table entry 'stptr' in tac->dest->val.stptr.
 *
 * Note that 'stptr' with type t_Array is not valid here!
 */
static void store_value_to_local( TAC *tac, int reg_num )
{
  symtabnode *stptr = tac->dest->val.stptr;

  switch ( stptr->type ) {
  case t_Int: // local int variable
    printf( "\tsw $%d, -%d($fp) # Store to local int %s.\n",
	    reg_num, stptr->offset2fp, stptr->name );
    break;
  case t_Char: // local char variable
    printf( "\tsb $%d, -%d($fp) # Store to local char %s.\n",
	    reg_num, stptr->offset2fp, stptr->name );
    break;
  case t_Tmp_Var: // local tmp variable
    printf( "\tsw $%d, -%d($fp) # Store to tmp variable %s.\n",
	    reg_num, stptr->offset2fp, stptr->name );
    break;
  case t_Tmp_Addr: // local tmp address (reference to an array element)
    if ( tac->optype == Assg ) {
      /* Whenever assignment a value to a t_Tmp_Addr, we mean assigning
	 the value to the array element it points to. */
          /* Load address into $(reg_num+1) first. */
      printf( "\tlw $%d, -%d($fp) # Load tmp address %s.\n",
	      reg_num+1, stptr->offset2fp, stptr->name );
      /* Load value of array element referenced by the address stored in $(reg_num+1). */
      if ( stptr->elt_type == t_Int ) {
	printf( "\tsw $%d, ($%d) # Store value pointed by %s to int array element.\n",
		reg_num, reg_num+1, stptr->name );
      } else {
	printf( "\tsb $%d, ($%d) # Store value pointed by %s to char array element.\n",
		reg_num, reg_num+1, stptr->name );
      }
    } else { // when it appears in arithmetic operation, like t_addr0 = A + 8
             // we just want to assign a value to t_Tmp_Addr, the value is an address.
      printf( "\tsw $%d, -%d($fp) # Store address to tmp address %s.\n",
	      reg_num, stptr->offset2fp, stptr->name );
    }
    break;
  default:
    fprintf( stderr,
	     "Symbol table entry type(%d) is invalid for a local variable as a dest!\n",
	     stptr->type );
    exit( -1 );
    break;
  }  
}

/**
 * Store the value in register $(reg_num) to address 'dest' in 'tac'.
 */
static void store_value_to_dest( TAC *tac, int reg_num )
{
  address *dest = tac->dest;
  
  if ( dest->val.stptr->scope == Global ) { // global varible
    store_value_to_global( dest->val.stptr, reg_num );
  } else { // local scope
    if ( dest->val.stptr->formal == true ) {
      store_value_to_formal( dest->val.stptr, reg_num );
    } else {
      store_value_to_local( tac, reg_num );
    }
  }
}

/**
 * Generate mips assembly for binary arithmetic operations:
 * +, -, *, /
 * given 'tac' in the form:
 * dest = operand1 + operand2
 *
 * For scope, either of them could be:
 * 1. Global
 * 2. Local
 *
 * For global scope, it could be:
 * 1. int variable:    t_Int
 * 2. char variable:   t_Char
 * 3. array address:   t_Array (can only appear as operand!)
 * 
 * For local scope, it could be:
 * 1. array reference: t_Tmp_Addr
 * 2. int variable:    t_Int
 * 3. char variable:   t_Char
 * 4. array address:   t_Array (can only appear as operand)
 * 5. tmp variable:    t_Tmp_var
 * 6. formal parameter:
 *    6-1. t_Int
 *    6-2. t_Char
 *    6-3. t_Array
 *    6-4. t_Tmp_Str (string constant, but this cannot appear as an operand!)
 *
 * Note that operand1 or operand2 cannot be int/char constant, because
 * in TAC generator, we always assign int/char constant to a tmp variable
 * first.
 */
static void tac2mips_binary_arith( TAC *tac )
{
  /* step1: Load the value of operand1 into register $8. */
  load_operand_to_reg( tac->operand1, REG_8 );

  /* step2: Load the value of operand2 into register $9. */
  load_operand_to_reg( tac->operand2, REG_9 );

  /* step3: Carry out computation with the result going to register $10. */
  switch( tac->optype ) {
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
  default:
    fprintf( stderr, "Invalid binary arithmetic operation type: %d\n",
	     tac->optype );
    exit( -1 );
  }

  /* step4: Store the value in $10 back to dest. */
  store_value_to_dest( tac, REG_10 );
}

/**
 * Generate mips assembly for unary minus operations:
 * given 'tac' in the form:
 * dest = -operand1
 */
static void tac2mips_unary_minus( TAC *tac )
{
  /* step1: Load the value of operand1 into register $8. */
  load_operand_to_reg( tac->operand1, REG_8 );

  /* step2: Carry out computation with the result going to register $10. */
  printf( "\tneg $10, $8\n" );

  /* step3: Store the value in $10 back to dest. */
  store_value_to_dest( tac, REG_10 );
}

/**
 * Load the value of RHS value in 'operand' into register $reg_num in the
 * context of assignment: LHS = RHS.
 *
 * RHS could be a int/char constant or a symbol table entry.
 */
static void load_rhs_to_reg( address *operand, int reg_num )
{
  switch ( operand->atype ) {
  case AT_Charcon: // char constant
    printf( "\tli $%d, %d # Load char constant.\n",
	    reg_num, operand->val.iconst );
    break;
  case AT_Intcon: // int constant
    if ( operand->val.iconst < MAX_16bits ) { // small int constant
      printf( "\tli $%d, %d # Load int constant shorter than 16-bits\n",
	      reg_num, operand->val.iconst );
    } else { // large int constant
      printf( "\tlui $%d, %d # Load higher 16-bits\n",
	      reg_num, operand->val.iconst >> 16 );
      printf( "\tori $%d, %d # Load lower 16-bits\n",
	      reg_num, operand->val.iconst & 0xffff );
    }
    break;
  case AT_StRef:
    /* In the case of assigment, RHS cannot be a t_Array, although
       load_operand_to_reg() handles t_Array case, it will never be processed
       in this case. So calling this function directly should be safe. */
    load_operand_to_reg( operand, reg_num );
    break;
  default:
    fprintf( stderr, "AT type %d is invalid as a RHS operand!\n", operand->atype );
  }
}

/**
 * Generate mips assembly for assignemnt operations
 * given 'tac' in the form:
 * dest = operand1
 *
 * For scope, either of them could be:
 * 1. Global
 * 2. Local
 *
 * For global scope, it could be:
 * 1. int variable:    t_Int
 * 2. char variable:   t_Char
 * 
 * For local scope, it could be:
 * 1. array reference: t_Tmp_Addr
 * 2. int variable:    t_Int
 * 3. char variable:   t_Char
 * 4. int/char constant: AT_Intcon or AT_Charcon (can be only as operand1)
 * 5. tmp variable:    t_Tmp_var
 * 6. formal parameter:
 *    6-1. t_Int
 *    6-2. t_Char
 */
static void tac2mips_assg( TAC *tac )
{
  /* step1: Load value of operand1 into $8. */
  load_rhs_to_reg( tac->operand1, REG_8 );

  /* step2: Store value in $8 to dest. */
  store_value_to_dest( tac, REG_8 );
}

/**
 * Generate mips assembly for entering a function given
 * 'tac' in the form of: "enter func operand1"
 * where operand1 is a AT_Intcon holding the size of the
 * stack for the function.
 */
static void tac2mips_enterfunc( TAC *tac )
{
  int stack_size = tac->operand2->val.iconst;
  
  printf( "\tla $sp, -8($sp) # Allocate space for old $fp and $ra\n" );
  printf( "\tsw $fp, 4($sp) # Save old $fp on stack\n" );
  printf( "\tsw $ra, 0($sp) # Save old $ra on stack\n" );
  printf( "\tla $fp, 0($sp) # Set up frame pointer\n" );
  printf( "\tla $sp, -%d($sp) # Allocate stack frame for locals/tmps\n",
	  stack_size );
}

/**
 * Generate mips assembly for returning from a function given
 * 'tac' in the form of: "return operand1"
 * where operand1 is a symbol table entry pointing to the value
 * to be returned.
 *
 * 'ret_type' is the type for the return value. It can only be one of:
 * 1. t_Int: int value
 * 2. t_Char: char value
 * 3. t_None: no return value (void).
 */
static void tac2mips_return( TAC *tac, int ret_type )
{
  if ( tac->operand1 != NULL ) { // non void return type.
    /* Load the return value into $v0. */
    load_operand_to_reg( tac->operand1, REG_V0 );
    if ( ret_type == t_Char ) { // convert int --> char
      printf( "\tsw $%d, -4($fp)\n", REG_V0 );
      printf( "\tlb $%d, -4($fp)\n", REG_V0 );
    }
  }

  /* Common routinue for returning from within a function. */
  printf( "\tla $sp, 0($fp) # Move stack pointer back to $fp.\n" );  
  printf( "\tlw $ra, 0($sp) # Restore return address.\n" );
  printf( "\tlw $fp, 4($sp) # Restore frame pointer.\n" );
  printf( "\tla $sp, 8($sp) # Restore stack pointer.\n" );
  printf( "\tjr $ra # jump back to the return address.\n" );
}

/**
 * Generate mips assembly for pushing a parameter for callee given
 * 'tac' in the form of: "param operand1"
 * where operand1 is a symbol table entry pointing to the value
 * to be pushed. It could be int/char value, or an array address.
 */
static void tac2mips_param( TAC *tac )
{
  symtabnode *stptr = tac->operand1->val.stptr; 

  /* Load the value of the parameter into $8. */
  load_operand_to_reg( tac->operand1, REG_8 );
  
  printf( "\tla $sp, -4($sp) # Allocate stack space for parameter %s.\n",
	  stptr->name );
  printf( "\tsw $8, 0($sp) # Push the parameter value.\n" );
}

/**
 * Generate mips assembly for calling a function give tac
 * in the form of: "call operand1 operand2"
 * where operand1 is the symbol table entry for the callee and
 * operand2 (AT_Intcon) holds the number of parameters passed
 * to callee.
 */
static void tac2mips_call( TAC *tac )
{
  /* No _prefix for these three function. */
  if ( strcmp(tac->operand1->val.stptr->name, "print_int") == 0 ||
       strcmp(tac->operand1->val.stptr->name, "print_string") == 0 ||
       strcmp(tac->operand1->val.stptr->name, "main") == 0 ) {
    printf( "\tjal %s\n", tac->operand1->val.stptr->name );
  } else {
    printf( "\tjal _%s\n", tac->operand1->val.stptr->name );
  }
  printf( "\tla $sp, %d($sp) # Pop parameters off the stack.\n",
	  tac->operand2->val.iconst * 4 );
}

/**
 * Generate mips assembly for retrieving the returned value from
 * a function given 'tac' in the form of "retrieve operand1' if
 * if that function's return type is non void.
 */
static void tac2mips_retrieve( TAC *tac )
{
  /* In TAC generator, we always create a tmp varible
     to hold the return value. */
  if ( tac->operand1 != NULL ) { // non void return
    printf( "\tsw $%d, -%d($fp) # Store returned value to tmp variable %s.\n",
	    REG_V0, tac->operand1->val.stptr->offset2fp, tac->operand1->val.stptr->name );
  }
}

/**
 * Generate mips assembly for binary relational operation given
 * 'tac' in the form of "if operand1 op operand2 goto dest(label)".
 */
static void tac2mips_binary_cond( TAC *tac )
{
  /* step1: load the value of operand1 into $8. */
  load_operand_to_reg( tac->operand1, REG_8 );

  /* step2: load the value of operand1 into $9. */
  load_operand_to_reg( tac->operand2, REG_9 );

  switch ( tac->optype ) {
  case Equals:
    printf( "\tbeq $8, $9, %s\n", tac->dest->val.label );
    break;
  case Neq:
    printf( "\tbne $8, $9, %s\n", tac->dest->val.label );
    break;
  case Leq:
    printf( "\tble $8, $9, %s\n", tac->dest->val.label );
    break;
  case Lt:
    printf( "\tblt $8, $9, %s\n", tac->dest->val.label );
    break;
  case Geq:
    printf( "\tbge $8, $9, %s\n", tac->dest->val.label );
    break;
  case Gt:
    printf( "\tbgt $8, $9, %s\n", tac->dest->val.label );
    break;
  default:
    fprintf( stderr, "Invalid conditional test type: %d\n", tac->optype );
    exit( -1 );
  }
}

/**
 * Translate TACs to MIPS assembly for the syntax tree node 't' which
 * represents a function body with the return type as 'ret_type'.
 */
void tac2mips( tnode *t, int ret_type )
{
  TAC *tac;

  for ( tac = t->tac_seq->start; tac != NULL; tac = tac->next ) {
    if ( tac->optype == Noop ) { // dummy TAC
      continue;
    }
    switch ( tac->optype ) {
    case Plus:
    case BinaryMinus:
    case Mult:
    case Div:
      tac2mips_binary_arith( tac );
      break;
    case UnaryMinus:
      tac2mips_unary_minus( tac );
      break;
    case Assg:
      tac2mips_assg( tac );
      break;
    case Equals:
    case Neq:
    case Leq:
    case Lt:
    case Geq:
    case Gt:
      tac2mips_binary_cond( tac );
      break;
    case Label:
      printf( "\t.text\n" );
      if ( tac->operand1 != NULL ) { // means that it is a function label.
	/* add a prefix _ to avoid potential name conflicting with
	   MIPS reserved keywords.*/
	  /* No _prefix for these three function. */
	if ( strcmp(tac->dest->val.label, "print_int") == 0 ||
	     strcmp(tac->dest->val.label, "print_string") == 0 ||
	     strcmp(tac->dest->val.label, "main") == 0 ) {
	  printf( "%s:", tac->dest->val.label );
	} else {
	  printf( "_%s:", tac->dest->val.label );
	}
      } else {
	printf( "%s:", tac->dest->val.label );
      }
      break;
    case Goto:
      printf( "\tj %s\n", tac->dest->val.label );
      break;
    case Return:
      tac2mips_return( tac, ret_type );
      break;
    case Param:
      tac2mips_param( tac );
      break;
    case Call:
      tac2mips_call( tac );
      break;
    case Retrieve:
      tac2mips_retrieve( tac );
      break;
    case Enter:
      tac2mips_enterfunc( tac );
      break;
    case Stringcon:
      /* Ignore TAC for string constant since it will be handled
	 in tac2mips_param(). */
      break;
    default:
      break;
    }
  }
}
