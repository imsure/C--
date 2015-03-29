/**
 * Implementation of a bit vector (array) using unsigned int.
 * **********************************************************
 *
 * Author: Shuo Yang
 * Email: imsure95@gmail.com
 */

#include "bitvector.h"

/**
 * Compute and return the difference of two bit vectors of the same length 'len':
 * 'bv1' - 'bv2'
 */
bitvec *bv_diff( bitvec *bv1, bitvec *bv2, int len )
{
  bitvec *bv3 = NEW_BV( len );
  int i;
  for ( i = 0; i <= len/UINT_SZ; ++i ) {
    bv3[ i ] = bv1[ i ] & ~bv2[ i ];
  }
  return bv3;
}

/**
 * Compute and return the union of two bit vectors 'bv1' and 'bv2'
 * of the same length 'len'.
 */
bitvec *bv_union( bitvec *bv1, bitvec *bv2, int len )
{
  bitvec *bv3 = NEW_BV( len );
  int i;
  for ( i = 0; i <= len/UINT_SZ; ++i ) {
    bv3[ i ] = bv1[ i ] | bv2[ i ];
  }
  return bv3;  
}

/**
 * Compute and return the intersection of two bit vectors 'bv1' and 'bv2'
 * of the same length 'len'.
 */
bitvec *bv_intersec( bitvec *bv1, bitvec *bv2, int len )
{
  bitvec *bv3 = NEW_BV( len );
  int i;
  for ( i = 0; i <= len/UINT_SZ; ++i ) {
    bv3[ i ] = bv1[ i ] & bv2[ i ];
  }
  return bv3;  
}

void print_bv( const char *name, bitvec *bv, int len )
{
  int i;
  printf( "Bit vector %s: ", name );
  for ( i = len/UINT_SZ; i >= 0; --i ) {
    printf( "(%d:0x%x) ", i, bv[i] );
  }
  putchar( '\n' );
}
