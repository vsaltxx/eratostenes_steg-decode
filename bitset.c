// bitset.c
// Řešení IJC-DU1, příklad a), 21.3.2023
// Autor: Veranika Saltanava, FIT
// Přeloženo: gcc 11.3.0

#ifdef USE_INLINE

#include "bitset.h"

/*
 * Extern declaration of inline functions from bitset.h
 */
extern void bitset_free(bitset_t array);
extern unsigned long bitset_size(bitset_t array);
extern void bitset_setbit(bitset_t array, bitset_index_t index, int expression);
extern int bitset_getbit(bitset_t array, bitset_index_t index);


#endif //USE_INLINE