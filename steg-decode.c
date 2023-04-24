// steg-decode.c
// Řešení IJC-DU1, příklad b), 21.3.2023
// Autor: Veranika Saltanava, FIT
// Přeloženo: gcc 11.3.0


#include "steg-decode.h"
#define START_PRIME 101

void msg_decode(struct ppm *image, unsigned long data_size, bitset_t image_bitset) {

    // msg_bitset is a bitset of the message data
    char msg_bitset[8];

    bitset_index_t msg_index = 0;

    for (unsigned long i = START_PRIME; i < data_size; i++) {
        if (bitset_getbit(image_bitset, i) == 0) {
            bitset_setbit(msg_bitset, msg_index, (image->data[i] & 1));
            msg_index++;
            if (msg_index == 8) {
                if (msg_bitset[1] == '\0') { // End of message ; 0 is the ASCII value for null
                    printf("\n");
                    return;
                }
                else {
                        printf("%c", (char)msg_bitset[1]);
                        msg_index = 0;
                }
            }
        }
    }
    // Check if msg_bitset is null terminated
    if (msg_bitset[1] != '\0') {
        error_exit("steg-decode: End of string sign (null) is missing.");
    }

}



int main(int argc, char *argv[]) {

    if (argc != 2) {
        error_exit("steg-decode: Invalid number of arguments.");
    }

    char filename[strlen(argv[1])];
    strcpy(filename, argv[1]);

    struct ppm *image = ppm_read(filename);
    if (image == NULL) {
        error_exit("steg-decode: Image reading failed.");
    }

    unsigned long data_size = 3 * image->xsize * image->ysize;


    // image_bitset is a bitset of the image data
    bitset_t image_bitset;

    bitset_alloc(image_bitset, data_size);
    bitset_create(image_bitset, data_size);

    Eratosthenes(image_bitset);

    msg_decode(image, data_size, image_bitset);


    // Free the memory allocated for the image
    bitset_free(image_bitset);
    ppm_free(image);

}