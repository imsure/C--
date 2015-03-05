#include "global.h"
#include "symbol-table.h"

extern int yydebug;
extern int yyparse();
//extern int mips_print_int();
//extern int mips_print_string();

int status = 0;

int main(void)
{
  SymTabInit(Global);
  SymTabInit(Local);

  //  mips_print_int();
  //  mips_print_string();
  
  if (yyparse() < 0) {
    printf("main: syntax error\n");
    status = 1;
  }
  
  return status;
}
