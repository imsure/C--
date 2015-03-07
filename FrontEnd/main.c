#include "global.h"
#include "symbol-table.h"

extern int yydebug;
extern int yyparse();
extern void spim_print_int();
extern void spim_print_string();

int status = 0;

int main(void)
{
  SymTabInit(Global);
  SymTabInit(Local);

  spim_print_int();
  spim_print_string();
  
  if (yyparse() < 0) {
    printf("main: syntax error\n");
    status = 1;
  }
  
  return status;
}
