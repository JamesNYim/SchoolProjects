#include "stats.h"

#include <stdint.h>

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        uint32_t j = i;
        uint32_t tempValue = move(stats, A[j]);
        while (j > 0 && (cmp(stats, tempValue, A[j - 1]) < 0)) {
            A[j] = move(stats, A[j - 1]);
            j--;
        }
        A[j] = move(stats, tempValue);
    }
}
