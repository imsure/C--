void foo(void)
{
  int x;
  int y;
  x = 0;
  y = 10;

  if (x != 0 && y < 10 && x == y) {
    y = x * x;
  } else {
    y = x;
  }

  x = x / 2;
}

void bar(void)
{
  int x;
  int y;
  x = 0;
  y = 10;

  if (x != 0 || y < 10 || x == y) {
    y = x * x;
  } else {
    y = x;
  }

  x = x / 2;
}

