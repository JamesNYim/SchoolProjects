#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bv.h"
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

//Creating the bitvector
BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector));

    //checking if bit vector was successfully allocated
    if (bv) {
        bv->length = length;
        bv->vector = (uint8_t *) calloc(length, sizeof(uint8_t));
        if (bv->vector) {
            return bv;
        }
        free(bv);
    }
    return NULL;
}

//Deleting the bit vector
void bv_delete(BitVector **bv) {
    if (bv) {
        free((*bv)->vector);
        free(*bv);
    }
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    //If the index is out of bounds
    if (i / 8 > bv_length(bv) || i < 0) {
        return false;
    }

    //setting bit at index i to 1
    bv->vector[i / 8] |= (0x1 << (i % 8));
    return true;
}
bool bv_clr_bit(BitVector *bv, uint32_t i) {
    //If the index is out of bounds
    if (i / 8 > bv_length(bv) || i < 0) {
        return false;
    }

    //setting bit at index i to 0
    bv->vector[i / 8] &= ~(0x1 << (i % 8));
    return true;
}
bool bv_get_bit(BitVector *bv, uint32_t i) {
    //If the index is out of bounds
    if (i / 8 > bv_length(bv) || i < 0) {
        return false;
    }

    if (((bv->vector[i / 8] >> i % 8) & 0x1) == 1) {
        return true;
    }
    return false;
}

void bv_print(BitVector *bv) {
    for (uint32_t currentByte = 0; currentByte < bv_length(bv); currentByte++) {
        printf("[%u], ", bv->vector[currentByte]);
    }
    printf("\n");
}
