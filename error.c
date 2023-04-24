// error.c
// Řešení IJC-DU1, příklad b), 21.3.2023
// Autor: Veranika Saltanava, FIT
// Přeloženo: gcc 11.3.0

#include "error.h"

/*
 * va_list - variable type; a pointer to a list of function arguments.
 * fmt - format string that specifies where the argument list starts.
 * va_start - sets the pointer to the beginning of the argument list.
 * fprintf - to write a formatted text to the stream; fixed number of arguments
 * vprintf - same as fprintf, but variable number of arguments.
 * va_end - to terminate work with a variable number of arguments;
 *          stack clean up of the arguments list.
 */


/*
 * Prints an error message starting with the word "Warning" to the
 * standard stderr output
 */
void warning(const char *fmt, ...) {

    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}


/*
 * Prints a message starting with the word "Error" and then exits the program
 * by calling the exit(1) function.
 */
void error_exit(const char *fmt, ...) {

    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}