/*
 * testgcsub6-incorrect.c: checks for correctness of global
 * common subexpression elimination.
 */
/**********/
extern void print_int(int n) ;
extern void print_string(char s[]);
/**********/

void main(void) 
{
  int A[4], i, j, z;
  
  for (i = 0; i < 4; i = i+1) {
    A[i] = i;  /* initialize */
  }
  
  j = i-2;
  i = i/2;
  
  /* both i and j should have the value 2 here */
  z = i + A[i];
  
  A[j] = 0;      /* since i == j, this defines A[i] */
  
  z = i + A[i];  /* this should not be optimized away */

  print_int(z);
  print_string("\n");  
}
