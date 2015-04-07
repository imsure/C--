/* simple while loops */
extern void print_int (int n);
extern void print_string (char s[]);

void bubble_sort( int A[], int n )
{
  int i, tmp, swap_counter;

  swap_counter = 0;
  for ( i = 0; i < 9; i = i + 1 ) {
    if ( A[i] > A[i+1] ) {
      /* swap */
      tmp = A[i];
      A[i] = A[i+1];
      A[i+1] = tmp;
      swap_counter = swap_counter + 1;
    }
  }

  while ( swap_counter > 0 ) {
      swap_counter = 0;
      for ( i = 0; i < 9; i = i + 1 ) {
	if ( A[i] > A[i+1] ) {
	  /* swap */
	  tmp = A[i];
	  A[i] = A[i+1];
	  A[i+1] = tmp;
	  swap_counter = swap_counter + 1;
	}
      }
  }
}

void main(void)
{
  int i;
  int A[10];

  A[0] = 9;
  A[1] = 8;
  A[2] = 7;
  A[3] = 6;
  A[4] = 5;
  A[5] = 4;
  A[6] = 3;
  A[7] = 2;
  A[8] = 1;
  A[9] = 0;

  print_string( "Before bubble sort:" );
  print_string("\n");
  for ( i = 0; i < 10; i = i + 1 ) {
    print_int( A[i] );
    print_string("\n");
  }

  bubble_sort( A, 10 );

  print_string( "After bubble sort:" );
  print_string("\n");
  for ( i = 0; i < 10; i = i + 1 ) {
    print_int( A[i] );
    print_string("\n");
  }
}
