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

/**
 * Check if two bit vectors 'bv1' and 'bv2' are not equal.
 * if bv1 != bv2, return true; otherwise false.
 */
bool bv_unequal_check( bitvec *bv1, bitvec *bv2, int len )
{
  int i;
  for ( i = 0; i <= len/UINT_SZ; ++i ) {
    if ( bv1[ i ] != bv2[ i ] ) {
      return true;
    }
  }
  return false;
}

void print_bv( const char *name, bitvec *bv, int len )
{
  int i;
  printf( "%s: ", name );
  for ( i = len/UINT_SZ; i >= 0; --i ) {
    printf( "(%d:0x%x) ", i, bv[i] );
  }
  putchar( '\n' );
}

bool bv_test_bit( bitvec *bv, int k )
{
  if ( bv[k/UINT_SZ] & (0x1 << (k % UINT_SZ)) ) {
    return true;
  } else {
    return false;
  }
}

/**
 * Return the position of the least significant 1 in 'bv'.
 */
static int bv_ls1( bitvec *bv, int len )
{
  int i, j;
  for ( i = 0; i <= len/UINT_SZ; ++i ) {
    for ( j = 0; j < UINT_SZ; ++j ) {
      if ( bv_test_bit( bv, i*UINT_SZ + j ) ) {
	return i*UINT_SZ + j + 1;
      }
    }
  }
  return 0;
}

/**
 * Return the position of the most significant 1 in 'bv'.
 */
static int bv_ms1( bitvec *bv, int len )
{
  int i, j;
  for ( i = len/UINT_SZ; i >= 0; --i ) {
    for ( j = UINT_SZ-1; j >= 0; --j ) {
      if ( bv_test_bit( bv, i*UINT_SZ + j ) ) {
	return i*UINT_SZ + j + 1;
      }
    }
  }
  return 0;
}

static bool in_range( int x, int min, int max )
{
  if ( x > min && x < max ) {
    return true;
  } else {
    return false;
  }
}

bool bv_have_overlap( bitvec *bv1, bitvec *bv2, int len )
{
  int pos_ls1 = bv_ls1( bv1, len );
  int pos_ms1 = bv_ms1( bv1, len );
  
  int pos_ls2 = bv_ls1( bv2, len );
  int pos_ms2 = bv_ms1( bv2, len );

  if ( in_range(pos_ls1, pos_ls2, pos_ms2) ) return true;
  if ( in_range(pos_ms1, pos_ls2, pos_ms2) ) return true;
  if ( in_range(pos_ls2, pos_ls1, pos_ms1) ) return true;
  if ( in_range(pos_ms2, pos_ls1, pos_ms1) ) return true;

  if ( pos_ls1 == pos_ls2 && pos_ms1 == pos_ms2 ) return true;

  return false;
}
