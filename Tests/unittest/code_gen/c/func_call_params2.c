/* function calls: multiple parameters */

int f(int a, char b, int c, char d, int e)
{
  return a+b*(c+d*e);
}

extern void print_int (int n);
extern void print_string (char s[]);

void main(void)
{
  int x;
  char y,z;

  y = 'a';
  z = 'b';
  
  x = f(1,2,3,4,5);
  x = f(x,y,x,z,x);
  print_int(x);
  print_string("\n");
}
