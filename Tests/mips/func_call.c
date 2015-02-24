extern void print_string( char str[] );
extern void print_int( int n );

void foo( int x )
{
  int y;
  y = x * 2;
  print_string("y = ");
  print_int( y );
  print_string("\n");
}

void main(void)
{
  foo( 5 );
}

