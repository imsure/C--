void foo(void)
{
  int x;
  x = 0;

  if (x > 0) {
    x = x - 1;
  } else {
    x = x + 1;
  }
}

void bar(void)
{
  int x, y, z;
  x = 1;
  y = 2;
  z = 3;
  
  if (x+y > 2*z) {
    z = x + y;
  } else {
    z = x - y;
  }

  z = (x + y) / 2;
}
