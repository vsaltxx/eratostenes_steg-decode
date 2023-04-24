// bitset.h
// Řešení IJC-DU1, příklad a), 21.3.2023
// Autor: Veranika Saltanava, FIT
// Přeloženo: gcc 11.3.0

#ifndef BITSET_H
#define BITSET_H

#include "primes.h"
#include <assert.h>
#include <string.h>

#define ULONG_BIT_SIZE (8 * sizeof(unsigned long))


// Definitions of data types for bitsets
typedef unsigned long* bitset_t;
typedef unsigned long bitset_index_t;

#ifndef USE_INLINE //if not USE_INLINE

/*
 * bitset_create - the static inicialization of bitfield
 *
 * The expression ((size - 1) / ULONG_BIT_SIZE ) calculates the number
 * of unsigned long integers required to store the bits in the bitset.
 * The + 2 at the end of the expression is used to allocate space for two
 * additional values in the bitset array. The first value is the size of the
 * bitset, which is stored as the first element of the array. The second
 * value is initialized to zero and is used to store any unused bits in the
 * last unsigned long integer.
 *
 * The resulting expression ((size - 1) / ULONG_BIT_SIZE) + 2) calculates
 * the total number of unsigned long integers required to store the bitset
 * of a given size, including space for the two additional values.
*/
#define bitset_create(array,size)                           \
    assert(size > 0);                                       \
    memset(array, 0, sizeof(unsigned long) * (((size - 1) / ULONG_BIT_SIZE) + 2)) ;           \
    array[0] = size;

/*
 * The dynamic inicialization of bitfield
 */
#define bitset_alloc(array, size)   \
    assert(size > 0);               \
    array = (bitset_t)calloc(((size-1) / ULONG_BIT_SIZE) + 2, sizeof(unsigned long));\
    assert (array != NULL);

/*
 *frees the memory of the dynamically (bitset_alloc) allocated array
 */
#define bitset_free(array) \
    free(array);
/*
 * Returns the size of bitset (contained in first element of bitset)
 */
#define bitset_size(array) \
    (array[0])

/*
 * bitset_setbit sets a bit at a definite index (index of fit in bitfield!!!)
 *
 * The + 1 in array index is needed to skip the first element of the array,
 * which contains the total number of bits in the bitset.
 *
 * 1ul - the unsigned long representation of the number 1.
 * The ULONG_BIT_SIZE constant represents the number of bits in an unsigned
 * long integer on the specific platform where the code is being compiled.
 * Therefore, the remainder of the division by this constant is always a
 * value between 0 and ULONG_BIT_SIZE - 1.
 *
 * For example, if ULONG_BIT_SIZE is equal to 32 (which is the case on most
 * modern 32-bit and 64-bit platforms), and the index value is equal to 12,
 * the expression 1ul << (12 % 32) evaluates to 1ul << 12, which shifts the
 * binary representation of the number 1 to the left by 12 positions:
 *
 * 00000000000000000000000000000001 (binary representation of 1)
 * << 12
 * 00000000000000000001000000000000 (binary representation of 1ul << 12)
*/
#define bitset_setbit(array,index, expression) \
    if (expression) { \
        (array)[(index) / ULONG_BIT_SIZE + 1] |= 1ul << ((index) % ULONG_BIT_SIZE); \
    } else {                                   \
        (array)[(index) / ULONG_BIT_SIZE + 1] &= ~(1ul << ((index) % ULONG_BIT_SIZE)); \
    }

/*
 * gets the value of the specified bit,
 * returns the value 0 or 1
*/

#define bitset_getbit(array, index) \
    ((index <= bitset_size(array))   \
    ?                               \
    (((array)[(index) / ULONG_BIT_SIZE + 1] & (1ul << ((index) % ULONG_BIT_SIZE))) != 0) \
    :                               \
    (error_exit("bitset_getbit: Index %lu is out of range 0..%lu",(unsigned long)index, (unsigned long)bitset_size(array) - 1),1))



#else //USE_INLINE

/*
 * ===== Inline functions to macros above =====
 */

#define bitset_create(array,size)                           \
    assert(size > 0);                                       \
    memset(array, 0, sizeof(unsigned long) * (((size - 1) / ULONG_BIT_SIZE) + 2)) ;           \
    array[0] = size;

#define bitset_alloc(array, size)   \
    assert(size > 0);               \
    array = (bitset_t)calloc(((size-1) / ULONG_BIT_SIZE) + 2, sizeof(unsigned long));\
    assert (array != NULL);


/* don't work because of static_assert
inline void bitset_create(bitset_t array, unsigned long size){
    static_assert(size > 0, "bitset_create: Invalid bitset size.");
    bitset_t array[((size-1) / ULONG_BIT_SIZE) + 2] = {0};
    array[0] = size;
}

inline void bitset_alloc(bitset_t array, unsigned long size){
    static_assert(size > 0, "bitset_alloc: Inalid bitset size.");
    bitset_t array = (bitset_t)calloc(((size-1) / ULONG_BIT_SIZE) + 2, sizeof(unsigned long));\
    assert (array != NULL);
}
*/
inline void bitset_free(bitset_t array){
    if (array == NULL){
        error_exit("Nothing to be freed.");
    }
    else {
        free(array);
        array = NULL;
    }
}

inline unsigned long bitset_size(bitset_t array){
    return array[0];
}

inline void bitset_setbit(bitset_t array, bitset_index_t index, int expression){
    if (index < bitset_size(array)) {
        if (expression) {
            (array)[(index) / ULONG_BIT_SIZE + 1] |= 1ul << ((index) % ULONG_BIT_SIZE);
        } else {                                   \
            (array)[(index) / ULONG_BIT_SIZE + 1] &= ~(1ul << ((index) % ULONG_BIT_SIZE));
        }
    }
    else {
        error_exit("bitset_getbit: Index %lu is out of range 0..%lu",(unsigned long)index, (unsigned long)(array[0] - 1));
    }
}


inline int bitset_getbit(bitset_t array, bitset_index_t index){
    if (index < bitset_size(array)) {
        return ((array[(index) / ULONG_BIT_SIZE + 1] & (1ul << ((index) % ULONG_BIT_SIZE))) != 0);
    }
    else {
        error_exit("bitset_getbit: Index %lu is out of range 0..%lu",(unsigned long)index, (unsigned long)(array[0] - 1));
        return 1;
    }
}



#endif //USE_INLINE
#endif //BITSET_H
