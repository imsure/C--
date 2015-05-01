/*
 * testgcsub2.c -- common subexpressions involving globals.
 *
 * This program checks for common subexpressions within a 
 * single basic block.  If common subexpression elimination
 * is performed, the instruction counts for this progam
 * should be significantly better than for testgcsub2-base.c.
 */

/**********/
extern void print_int(int n);
extern void print_string(char s[]);
/**********/


int n;

void main(void)
{
  int i, j, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9;
  
  n = 1;
  j = 0;

  /* common subexpressions within a single basic block */
  for (i = 0; i < 10000; i = i+1) {
    x0 = n*2;
    j = j + x0;
    x1 = n*2;
    j = j + x1;
    x2 = n*2;
    j = j + x1;
    x3 = n*2;
    j = j + x3;
    x4 = n*2;
    j = j + x4;
    x5 = n*2;
    j = j + x5;
    x6 = n*2;
    j = j + x6;
    x7 = n*2;
    j = j + x7;
    x8 = n*2;
    j = j + x8;
    x9 = n*2;
    j = j + x9;
  }
  
  print_int(j);
  print_string("\n");

}
