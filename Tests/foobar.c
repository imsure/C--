/**
 * A simple c-- function.
 */

int foo(int x);
void bar(void);

int main(void)
{
  int a;
  a = foo(5);
  bar();

  return 0;
}

int foo(int x)
{
  return x+1;
}

void bar(void)
{
  char c;
  c = 'b';
}
