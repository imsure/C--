/*
 * testgcsub5-incorrect.c: checks for correctness of global
 * common subexpression elimination.
 */
/**********/
extern void print_int(int n);
extern void print_string(char s[]);
/**********/

void main(void) 
{
  int x, y, z;
  
  x = 1;
  y = 2;
  z = x+y;

  if (z > y) {
    x = x+1;
  }
  
  z = x+y;  /* this should not be optimized out */
  
  print_int(z);
  print_string("\n");  
}
