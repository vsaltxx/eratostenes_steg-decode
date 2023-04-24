// primes.c
// Řešení IJC-DU1, příklad a), 21.3.2023
// Autor: Veranika Saltanava, FIT
// Přeloženo: gcc 11.3.0

#include <time.h>
#include "bitset.h"
#include "eratosthenes.h"

#define RANGE_END 230000000

#define LAST_N 10

int main(void) {

    clock_t start = clock();
    bitset_t array = NULL;

    bitset_alloc(array, RANGE_END);
    bitset_create(array, RANGE_END);

    Eratosthenes(array);

    print_last_primes(array, RANGE_END, LAST_N);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    bitset_free(array);

    return 0;
}
