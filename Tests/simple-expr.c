int g;

void foo(void)
{
  int x;
  int y;
  int z;

  x = 1;
  y = 2;
  z = -3;
  g = x + y + z;

  y = x * 8;
  z = y / x;
  x = z - y;

  z = -x;
}
