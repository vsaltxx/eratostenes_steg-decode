// eratosthenes.c
// Řešení IJC-DU1, příklad a), 21.3.2023
// Autor: Veranika Saltanava, FIT
// Přeloženo: gcc 11.3.0


#include "bitset.h"
#include "eratosthenes.h"

void Eratosthenes(bitset_t array)
{
    bitset_setbit(array, 1, 1); // 1 is not prime

    for (bitset_index_t  i = 2; i * i <= bitset_size(array); i++) {
        if (bitset_getbit(array, i) == 0) {
            for (bitset_index_t j = i + i; j < bitset_size(array); j += i) {
                bitset_setbit(array, j, 1);
            }
        }
    }
}

void print_last_primes(bitset_t array, bitset_index_t range_end, int last_N) {

    bitset_index_t reverse[last_N];
    int count = 0;

    for (bitset_index_t i = range_end - 1; i >= 2 && count < last_N; i--) {
        if (bitset_getbit(array, i) == 0) {
            reverse[count] = i;
            count++;
        }
    }
    printf("\n");

    for (int count = last_N - 1; count >= 0; count--){
        printf("%lu\n", reverse[count]);
    }

}
