#include "bv.h"
#include "bf.h"
#include "salts.h"
#include "speck.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct BloomFilter {
    uint64_t primary[2]; //primary hash function salt
    uint64_t secondary[2]; //secondary hash function salt
    uint64_t tertiary[2]; //Tertiary hash function salt
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    //Allocating Bloom Filter Container
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        //Setting Primary Salts
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;

        //Setting Secodary Salrs
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;

        //Setting Tertiary
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_HI;

        bf->filter = bv_create(size);
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter);
    free(*bf);
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *word) {
    //getting the 3 indicies
    uint32_t first_bit = hash(bf->primary, word) % bf_size(bf);
    uint32_t secondary_bit = hash(bf->secondary, word) % bf_size(bf);
    uint32_t tertiary_bit = hash(bf->tertiary, word) % bf_size(bf);

    //setting the bits at the indicies
    bv_set_bit(bf->filter, first_bit);
    bv_set_bit(bf->filter, secondary_bit);
    bv_set_bit(bf->filter, tertiary_bit);
}
bool bf_probe(BloomFilter *bf, char *word) {

    //getting the 3 indicies
    uint32_t first_bit = hash(bf->primary, word) % bf_size(bf);
    uint32_t secondary_bit = hash(bf->secondary, word) % bf_size(bf);
    uint32_t tertiary_bit = hash(bf->tertiary, word) % bf_size(bf);

    //Checking the 3 bits
    bool first_bool = bv_get_bit(bf->filter, first_bit);
    bool second_bool = bv_get_bit(bf->filter, secondary_bit);
    bool tertiary_bool = bv_get_bit(bf->filter, tertiary_bit);

    //returning value
    if (first_bool && second_bool && tertiary_bool) {
        return true;
    }
    return false;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
