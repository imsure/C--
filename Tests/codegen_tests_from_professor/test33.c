/* array assignments: local --> local */

extern void print_int (int n);
extern void print_string (char s[]);

void main(void)
{
  int x[10];
  int y[10];
  int u;

  y[7] = 1234;
  x[0] = y[7];
  u = x[0];
  print_int(u);
  print_string("\n");
}
