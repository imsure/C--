#include "global.h"
#include "symbol-table.h"

extern int yydebug;
extern int yyparse();
extern void spim_print_int();
extern void spim_print_string();

int status = 0;
bool perform_O1 = false; // indicate whether perform -O1 optimization or not.
bool tac_only = false; // indicate whether output TAC files only
bool output_mips = true;

int main( int argc, char *argv[] )
{
  if ( argc > 1 ) {
    /* Get the first argument */
    if ( strcmp( argv[1], "-O1") == 0 ) {
      perform_O1 = true;
    } 
    if ( argc > 2 ) {
      if ( strcmp( argv[2], "-TAC") == 0 ) {
	tac_only = true;
	output_mips = false;
      }
    } else { // only one argument
      if ( strcmp( argv[1], "-TAC") == 0 ) {
	tac_only = true;
	output_mips = false;
      } else {
	output_mips = true;
      }
    }
  } else { // no args, print mips code
    output_mips = true;
  }

  SymTabInit(Global);
  SymTabInit(Local);

  if ( output_mips == true ) {
    spim_print_int();
    spim_print_string();
  }

  if (yyparse() < 0) {
    printf("main: syntax error\n");
    status = 1;
  }
  
  return status;
}
