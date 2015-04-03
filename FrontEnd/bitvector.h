#ifndef BITVECTOR_H
#define BITVECTOR_H

#include "global.h"

#define UINT_SZ 32

/* Allocate space for a bit vector with the length 'len'. */
#define NEW_BV( len ) \
  (bitvec *) zalloc( ((len)/UINT_SZ+1) * sizeof(bitvec) )

/* Set the 'k'th bit of the bit vector 'A' to 1. */
#define SET_BIT(A, k) ( (A)[(k)/UINT_SZ] |= (0x1 << ((k) % UINT_SZ)) )

/* Set the 'k'th bit of the bit vector 'A' to 1. */
#define CLEAR_BIT(A, k) \
  ( A[(k)/UINT_SZ] &= ~(0x1 << ((k) % UINT_SZ)) )

/* Test if the 'k'th bit of the bit vector 'A' has been set to 1. */
#define TEST_BIT(A, k) \
  ( (A)[(k)/UINT_SZ] & (0x1 << ((k) % UINT_SZ)) )

bitvec *bv_diff( bitvec *bv1, bitvec *bv2, int len );
bitvec *bv_union( bitvec *bv1, bitvec *bv2, int len );
bitvec *bv_intersec( bitvec *bv1, bitvec *bv2, int len );
bool bv_unequal_check( bitvec *bv1, bitvec *bv2, int len );
void print_bv( const char *name, bitvec *bv, int len );
bool bv_test_bit( bitvec *bv, int k );
bool bv_have_overlap( bitvec *bv1, bitvec *bv2, int len );
int bv_ls1( bitvec *bv, int len );

#endif
