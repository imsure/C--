int foo(int x, int y);

void main(void)
{
  int a;
  a = 6;
  a = foo( 5, (a*2)/3 );
}

int foo(int x, int y)
{
  int z;
  z = x + y;
  return z;
}
