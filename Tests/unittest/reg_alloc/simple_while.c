/* simple while loops */
extern void print_int (int n);
extern void print_string (char s[]);

void main(void)
{
  int x;
  int z;

  x = 0;
  z = 1;
  while (z > 0) {
    x = x + 1;
    if (x > 10) {
      z = -1;
    }
  }

  print_int(x);
  print_string("\n");
  print_int(z);
  print_string("\n");
}
