#include "stats.h"

#include <inttypes.h>
uint32_t bitLengths(uint32_t n) {
    uint32_t count = 0;
    while (n > 0) {
        count++;
        n /= 2;
    }
    return count;
}

void comparator(Stats *stats, uint32_t *A, uint32_t greater, uint32_t lesser) {
    if (cmp(stats, A[greater], A[lesser]) > 0) {
        swap(stats, &A[lesser], &A[greater]);
    }
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t lengthOfArray) {
    if (lengthOfArray == 0) {
        return;
    }
    uint32_t bitLength = bitLengths(lengthOfArray);
    uint32_t p = 1 << (bitLength - 1);

    while (p > 0) {
        uint32_t q = 1 << (bitLength - 1);
        uint32_t r = 0;
        uint32_t d = p;

        while (d > 0) {
            for (uint32_t i = 0; i < lengthOfArray - d; i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
