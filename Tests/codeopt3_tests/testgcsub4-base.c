/*
 * testgcsub4-base.c -- common subexpressions involving globals.
 * This program sets up a baseline for testgcsub4.c.
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
    if (i > 1) {
      j = j+1;
    }

    j = j + n*3;
    if (i > 5) {
      j = j+1;
    }

    j = j + n*4;
    if (i > 10) {
      j = j+1;
    }

    j = j + n*5;
    if (i > 50) {
      j = j+1;
    }

    j = j + n*6;
    if (i > 100) {
      j = j+1;
    }

    j = j + n*7;
    if (i > 500) {
      j = j+1;
    }

    j = j + n*8;
    if (i > 1000) {
      j = j+1;
    }

    j = j + n*9;
    if (i > 5000) {
      j = j+1;
    }

    j = j + n*10;
    if (i > 10000) {
      j = j+1;
    }

    j = j + n*11;
  }
  
  print_int(j);
  print_string("\n");

}
