extern void print_string( char str[] );
extern void print_int( int n );

void bar( int x, int y )
{
  int z;
  z = x * y;

  print_string("bar: z = ");
  print_int( z );
  print_string("\n");
}

int foo( int x, int y )
{
  int z;
  z = x + y;

  print_string("foo: z = ");
  print_int( z );
  print_string("\n");

  bar( x, y );
  return z;
}

void main(void)
{
  int A[5];
  int z;
  A[0] = 7;
  z = foo( 5, A[0] );

  print_string("main: z = ");
  print_int( z );
  print_string("\n");

}

