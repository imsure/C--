#ifndef BITVECTOR_H
#define BITVECTOR_H

#include "global.h"

#define UINT_SZ 32

typedef unsigned int bitvec;

/* Allocate space for a bit vector with the length 'len'. */
#define NEW_BV( len ) \
  (bitvec *) zalloc( (len/UINT_SZ+1) * sizeof(bitvec) )

/* Set the 'k'th bit of the bit vector 'A' to 1. */
#define SET_BIT(A, k) ( A[k/UINT_SZ] |= (0x1 << (k % UINT_SZ)) )

bitvec *bv_diff( bitvec *bv1, bitvec *bv2, int len );
bitvec *bv_union( bitvec *bv1, bitvec *bv2, int len );
bitvec *bv_intersec( bitvec *bv1, bitvec *bv2, int len );

#endif
