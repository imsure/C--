/*
 * testgcsub6-incorrect.c: checks for correctness of global
 * common subexpression elimination.
 */
/**********/
extern void print_int(int n);
extern void print_string(char s[]);
/**********/

int i;

void side_effect(int n)
{
  i = i+n;
}

void main(void) 
{
  int A[4], z;
  
  for (i = 0; i < 4; i = i+1) {
    A[i] = i;  /* initialize */
  }
  
  i = 2;

  z = i + A[i];

  side_effect(1);
  
  z = i + A[i];  /* this should not be optimized away */

  print_int(z);
  print_string("\n");  
}
