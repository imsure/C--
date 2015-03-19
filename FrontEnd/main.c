#include "global.h"
#include "symbol-table.h"
#include <unistd.h>

extern int yydebug;
extern int yyparse();
extern void spim_print_int();
extern void spim_print_string();

int status = 0;
bool perform_O1 = false; // indicate whether perform -O1 optimization or not.
bool perform_O2 = false; // indicate whether perform -O2 optimization or not.
bool tac_only = false; // indicate whether output TAC files only

/**
 * Print out help info.
 */
static void print_help()
{
}

int main( int argc, char *argv[] )
{
  char c;
  
  /**
   * Parsing command line arguments.
   */
  while ( (c = getopt(argc, argv, "O:T:Hh")) != -1 ) {
    switch ( c ) {
    case 'O':
      if ( optarg != NULL ) {
	switch ( optarg[0] ) {
	case '1':
	  perform_O1 = true; break;
	case '2':
	  perform_O2 = true; break;
	default:
	  break;
	}
      }
      break;
    case 'T':
      if ( strcmp(optarg, "AC") == 0 ) {
	tac_only = true;
      }
      break;
    case 'H':
    case 'h':
      print_help();
      exit( 0 );
    default:
      printf( "Invalid option: %c\n", c );
      break;
    }
  }

  SymTabInit(Global);
  SymTabInit(Local);

  if ( tac_only == false ) {
    spim_print_int();
    spim_print_string();
  }

  if (yyparse() < 0) {
    printf("main: syntax error\n");
    status = 1;
  }
  
  return status;
}
