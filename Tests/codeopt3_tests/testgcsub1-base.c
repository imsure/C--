/*
 * testgcsub1-base.c -- common subexpressions involving globals.
 * This program sets up a baseline for testgcsub1.c
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

  for (i = 0; i < 10000; i = i+1) {
    j = j + n*2;
    j = j + n*3;
    j = j + n*4;
    j = j + n*5;
    j = j + n*6;
    j = j + n*7;
    j = j + n*8;
    j = j + n*9;
    j = j + n*10;
    j = j + n*11;
  }
  
  print_int(j);
  print_string("\n");

}
