extern void print_int( int n );
extern void print_string( char str[] );

void main( void )
{
  int x ,y, z;
  char c;
  char str[7];
   int A[5];
  
  x = 10; /* constant assigned to local */
  print_int( x );
  print_string( "\n" );

  str[ 1 ] = 45;
  print_int( str[1] );
  print_string( "\n" );

  str[3] = 21;
  y = str[3];
  print_int( y );
  print_string( "\n" );

  c = 90;
  print_int( c );
  print_string( "\n" );

  A[0] = str[3];
  z = A[0];
  print_int( z );
  print_string( "\n" );

  print_int( 45 );
  print_string( "\n" );

  y = x + 50;
  print_int( y );
  print_string( "\n" );
  
  z = y/10;
  print_int( z );
  print_string( "\n" );
}
