int G[ 2 ];

void foo(void)
{
  int x;
  int y;
  int A[ 2 ];

  x = 0;
  y = 1;
  A[0] = 8;
  A[y] = x;

  G[0] = A[y];
}
