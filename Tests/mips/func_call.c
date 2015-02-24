extern void print_string( char str[] );
extern void print_int( int n );

void foo( int x, int y )
{
  int z, z1, z2;
  z1 = x;
  z2 = y;

  print_string("z1 = ");
  print_int( z1 );
  print_string("\n");

  print_string("z = ");
  print_int( z1 + z2 );
  print_string("\n");
}

void main(void)
{
  int A[5];

  A[0] = 7;
  foo( 5, A[0] );

  print_string( "A[1] = " );
  print_int( A[0] - 3 );
  print_string( "\n" );
}

