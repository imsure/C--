/* simple func call, it reveals bug of
   register allocation when the callee is
   not executed in the runtime becasue of
   some condition is not true. */
extern void print_int (int n);
extern void print_string (char s[]);

void func(void)
{
  int z;
  z = 5;
}

void main(void)
{
  int x;
  int y;

  x = 1; y = 2;
  if ( x < y )
    func();

  print_int(x);
  print_string("\n");
}
