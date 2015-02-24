extern void print_string( char str[] );
extern void print_int( int n );

void foo( int A[], int n )
{
  print_string("n = ");
  print_int( A[1] );
  print_string("\n");
}

void main(void)
{
  int B[5];
  B[0] = 46;
  B[1] = 78;
  B[2] = 36;
  foo( B, 21 );
}

