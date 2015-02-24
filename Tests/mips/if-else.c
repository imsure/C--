extern void print_int( int n );
extern void print_string( char str[] );

void main( void )
{
  int x ,y, z;
  
  x = 10; /* constant assigned to local */
  if ( x > 10 ) {
    print_string( "Then..." );
    print_string( "\n" );
  } else {
    print_string( "Else..." );
    print_string( "\n" );
  }
}
