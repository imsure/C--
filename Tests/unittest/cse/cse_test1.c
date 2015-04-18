extern void print_int (int n);
extern void print_string (char s[]);

void main(void)
{
  int x,y,z,w;

  x = 0;
  y = 1;

  z = x + y;
  w = x + y;

  print_int(z);
  print_string("\n");
  print_int(w);
  print_string("\n");
}
