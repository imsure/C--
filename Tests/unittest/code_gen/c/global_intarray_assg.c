/* array assignments: global --> global */

int x[10];
int y[10];

extern void print_int (int n);
extern void print_string (char s[]);

void main(void)
{
  int u;

  y[7] = 1234;
  x[0] = y[7];
  u = x[0];
  print_int(u);
  print_string("\n");
}
