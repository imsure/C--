/*
 * testgcsub4.c -- common subexpressions involving globals.
 *
 * This program checks for common subexpressions across basic
 * block boundaries.  If common subexpression elimination
 * is performed, the instruction counts for this progam
 * should be significantly better than for testgcsub4-base.c.
 */

/**********/
extern void print_int(int n) ;
extern void print_string(char s[]);
/**********/


int n;

void main(void)
{
  int i, j;
  
  n = 1;
  j = 0;

  /* common subexpressions across basic block boundaries */
  for (i = 0; i < 10000; i = i+1) {
    j = j + n*2;
    if (i > 1) {
      j = j+1;
    }

    j = j + n*2;
    if (i > 5) {
      j = j+1;
    }

    j = j + n*2;
    if (i > 10) {
      j = j+1;
    }

    j = j + n*2;
    if (i > 50) {
      j = j+1;
    }

    j = j + n*2;
    if (i > 100) {
      j = j+1;
    }

    j = j + n*2;
    if (i > 500) {
      j = j+1;
    }

    j = j + n*2;
    if (i > 1000) {
      j = j+1;
    }

    j = j + n*2;
    if (i > 5000) {
      j = j+1;
    }

    j = j + n*2;
    if (i > 10000) {
      j = j+1;
    }

    j = j + n*2;
  }
  
  print_int(j);
  print_string("\n");

}
