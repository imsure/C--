/* references to elements of the same local array */

extern void print_int(int x);
extern void print_string(char str[]);

void main(void)
{
  int a[10];
  int i, j, k;

  i = 1; j = 1; k = 1;

  a[i] = 123;
  a[j] = 234;
  a[k] = 345;

  print_int(a[1]);
  print_string("\n");
}


  
