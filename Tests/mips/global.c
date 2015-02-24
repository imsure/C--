extern void print_int( int n );
extern void print_string( char str[] );

int gi;
char gc;
int ga[5];

void foo( char str[] )
{
  int x;
  char c;

  gi = 5;
  c = 'b';

  print_string( "gi = " );
  print_int( gi );
  print_string( "\n" );

  /* x = gi + 7; */
  /* print_string( "x = " ); */
  /* print_int( x ); */
  /* print_string( "\n" ); */

  gc = c;

  print_string( "gc = " );
  print_int( gc );
  print_string( "\n" );

  x = 0;
  x = gi;
  print_string( "x = " );
  print_int( x );
  print_string( "\n" );
}

void main( void )
{
  foo( "abc" );
}
