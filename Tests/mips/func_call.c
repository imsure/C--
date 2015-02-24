extern void print_string( char str[] );
extern void print_int( int n );

void foo( int x, int y, int A[] )
{
  int z;
  z = x * y;
  print_string("y = ");
  print_int( y );
  print_string("\n");
}

void main(void)
{
  int B[5];
  foo( 5, 6, B );
}

