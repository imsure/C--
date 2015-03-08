/* While follows a if: for testing callpsing jumping chain
   optimization. */

extern void print_int (int n);
extern void print_string (char s[]);

void main(void)
{
  int x, i;

  x = 123;
  if ( x == 123 ) 
    x = 321;

  while (x > 0) {
    x = x-1;
  }
  print_int(x);
  print_string("\n");
}

