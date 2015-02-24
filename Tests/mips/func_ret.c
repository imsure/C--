extern void print_string( char str[] );
extern void print_int( int n );

int bar( int x, int y )
{
  int z;
  z = x * y;

  print_string("bar: z = ");
  print_int( z );
  print_string("\n");

  return x*y;
}

int foo( int x, int y )
{
  int z;
  z = x + y;

  print_string("foo: z = ");
  print_int( z );
  print_string("\n");

  for ( z = 0; z <= (x+y); z = z+1 ) {
    print_string("foo:loop: z = ");
    print_int( z );
    print_string("\n");
  }

  x = bar( x, y );
  print_string("foo: x = ");
  print_int( x );
  print_string("\n");

  return z;
}

void main(void)
{
  int A[5];
  int z;
  A[0] = 7;
  A[1] = foo( 5, A[0] );

  print_string("main: A[1] = ");
  print_int( A[1] );
  print_string("\n");

}

