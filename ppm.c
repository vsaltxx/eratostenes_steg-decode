// ppm.c
// Řešení IJC-DU1, příklad b), 21.3.2023
// Autor: Veranika Saltanava, FIT
// Přeloženo: gcc 11.3.0


#include "ppm.h"

struct ppm * ppm_read(const char * filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        warning("ppm: File reading failed");
        return NULL;
    }

    char magic[3];

    // Check that the file format is correct
    if (fread(magic, 1, 3, f) != 3 || strncmp(magic, "P6\n", 3)) {
        warning("ppm: Not a PPM file");
        fclose(f);
        return NULL;
    }

    unsigned xsize, ysize;

    // Read the image size information and check that it is valid
    if (fscanf(f, "%u %u\n", &xsize, &ysize) != 2) {
        warning("ppm: Invalid image size (error loading '%s')", filename);
        fclose(f);
        return NULL;
    }

    unsigned maxval;
    if (fscanf(f, "%u\n", &maxval) != 1 || maxval != 255) {
        warning("ppm: Invalid max value (error loading '%s')", filename);
        fclose(f);
        return NULL;
    }

    // Allocate memory for the struct and check that it was successful
    struct ppm *image = (struct ppm *)malloc(sizeof(struct ppm) + 3 * xsize * ysize);
    if (!image) {
        warning("ppm: Memory allocation failed");
        fclose(f);
        return NULL;
    }

    image->xsize = xsize;
    image->ysize = ysize;

    // Read the image data and check that it was successful
    size_t bytes_read = fread(image->data, 1, 3 * xsize * ysize, f);
    if (bytes_read != 3 * xsize * ysize) {
        warning("ppm: Image file is truncated (error loading '%s')", filename);
        ppm_free(image);
        fclose(f);
        return NULL;
    }

    // Check that the file is not too long
    char c;
    if (fread(&c, 1, 1, f) == 1) {
        warning("ppm: Image file is too long (error loading '%s')", filename);
        ppm_free(image);
        fclose(f);
        return NULL;
    }

    // Close the file and return the image
    fclose(f);
    return image;

}


void ppm_free(struct ppm *p) {
    free(p);
}