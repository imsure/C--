/*
 * testgcsub3.c -- common subexpressions involving locals.
 *
 * This program checks for common subexpressions within a 
 * single basic block.  If common subexpression elimination
 * is performed, the instruction counts for this progam
 * should be significantly better than for testgcsub3-base.c.
 */

/**********/
extern void print_int(int n) ;
extern void print_string(char s[]);
/**********/


void main(void)
{
  int n;
  int i, j;
  
  n = 1;
  j = 0;

  /* common subexpressions within a single basic block */
  for (i = 0; i < 10000; i = i+1) {
    j = j + n*2;
    j = j + n*2;
    j = j + n*2;
    j = j + n*2;
    j = j + n*2;
    j = j + n*2;
    j = j + n*2;
    j = j + n*2;
    j = j + n*2;
    j = j + n*2;
  }
  
  print_int(j);
  print_string("\n");

}
