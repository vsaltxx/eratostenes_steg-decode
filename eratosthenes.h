// eratosthenes.h
// Řešení IJC-DU1, příklad a), 21.3.2023
// Autor: Veranika Saltanava, FIT
// Přeloženo: gcc 11.3.0

#ifndef ERATOSTHENES_H
#define ERATOSTHENES_H

#include "bitset.h"

/*
 * The declaration of the function from the eratosthenes.c module
 */

void Eratosthenes(bitset_t array);
void print_last_primes(bitset_t array, bitset_index_t range_end, int last_N);

#endif //ERATOSTHENES_H
