extern void print_int( int n );
extern void print_string( char str[] );

int gi;
char gc;
int ga[5];
char str[5];

void foo( char str[] )
{
  int x;
  char c;

  gi = 5;
  c = 'b';

  /* print_string( "gi = " ); */
  /* print_int( gi ); */
  /* print_string( "\n" ); */

  /* x = gi + 7; */
  /* print_string( "x = " ); */
  /* print_int( x ); */
  /* print_string( "\n" ); */

  /* gc = c; */

  /* print_string( "gc = " ); */
  /* print_int( gc ); */
  /* print_string( "\n" ); */

  /* x = 0; */
  /* x = gi; */
  /* print_string( "x = " ); */
  /* print_int( x ); */
  /* print_string( "\n" ); */

  /* gi = x + gc; */
  /* print_string( "gi = " ); */
  /* print_int( gi ); */
  /* print_string( "\n" ); */
  
  ga[0] = c;
  x = ga[0] + c;
  print_string( "ga[0] = " );
  print_int( x );
  print_string( "\n" );
}

void main( void )
{
  char c1, c2;
  /*foo( "abc" );*/

  c1 = 'c';
  c2 = 'd';
  print_string( "c1 = " );
  print_int( c1 );
  print_string( "\n" );

  print_string( "c2 = " );
  print_int( c2 );
  print_string( "\n" );

  str[0] = c1;
  str[1] = c2;

  print_string( "str0 = " );
  print_int( str[0] );
  print_string( "\n" );

  ga[1] = 5;
  print_string( "str1 = " );
  print_int( c1 + str[1] );
  print_string( "\n" );

}
