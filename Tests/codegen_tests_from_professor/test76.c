/* handling a large integer constant */

int x;

extern void print_int (int n);
extern void print_string (char s[]);

void main(void)
{
  x = 1234567890;
  print_int(x);
  print_string("\n");
}
