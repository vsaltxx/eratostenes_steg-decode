// ppm.h
// Řešení IJC-DU1, příklad b), 21.3.2023
// Autor: Veranika Saltanava, FIT
// Přeloženo: gcc 11.3.0

#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

/*
 * Declaration of the structure ppm from ppm.c
 */
struct ppm {
    unsigned int xsize;
    unsigned int ysize;
    char data[]; // RGB bytes, 3*xsize*ysize in total
};


/*
 * Declaration of the functions from ppm.c
 */
struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);



#endif //PPM_H
