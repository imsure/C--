void foo( int x );

void main(void)
{
  int y;
  foo( 6 );
  y = 4;
}

void foo( int x )
{
  x = x / 5;
}
