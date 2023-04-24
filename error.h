// error.h
// Řešení IJC-DU1, příklad b), 21.3.2023
// Autor: Veranika Saltanava, FIT
// Přeloženo: gcc 11.3.0

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/*
 * Declaration of functions from error.c
 */

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif //ERROR_H
