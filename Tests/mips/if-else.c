extern void print_int( int n );
extern void print_string( char str[] );

void main( void )
{
  int n, i, j;
  
  n = 10; /* constant assigned to local */
  if ( n > 10 ) {
    print_string( "Then..." );
    print_string( "\n" );
  } else {
    print_string( "Else..." );
    print_string( "\n" );
  }

  while ( n > 0 ) {
    print_string( "n = " );
    print_int(n);
    print_string( "\n" );
    n = n - 1;
  }

  for ( i = 0; i < 5; i = i+1 ) {
    print_string( "i = " );
    print_int( i );
    print_string( "\n" );
  }

  n = 10;
  while ( i <= n && i >= 0 ) {
    print_string( "i = " );
    print_int( i );
    print_string( "\n" );
    i = i - 1;
  }

  for ( i = 'a'; i < 'z'; i = i+1 ) {
    print_string( "i = " );
    print_int( i );
    print_string( "\n" );
  }

  i = -2;
  j = 5;
  n = 4;
  if ( j+i == n ) {
    print_string( "j + i == n " );
    print_string( "\n" );
  } else {
    print_string( "j + i != n " );
    print_string( "\n" );
  }
  print_string( "j + i = " );
  print_int( i + j );
  print_string( "\n" );

  i = -1;
  j = 5;
  n = 4;
  if ( !(j+i == n) ) {
    print_string( "j + i != n " );
    print_string( "\n" );
  } else {
    print_string( "j + i == n " );
    print_string( "\n" );
  }

}
