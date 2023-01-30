#include "stats.h"

#include <inttypes.h>
uint32_t partition(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    uint32_t partitionPoint = low - 1;
    for (uint32_t i = low; i < high; i++) {
        if (cmp(stats, A[i - 1], A[high - 1]) < 0) {
            partitionPoint++;
            swap(stats, &A[partitionPoint - 1], &A[i - 1]);
        }
    }
    swap(stats, &A[partitionPoint], &A[high - 1]);
    return partitionPoint + 1;
}

void quick_sorter(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    if (low < high) {
        int partitionPoint = partition(stats, A, low, high);
        quick_sorter(stats, A, low, partitionPoint - 1);
        quick_sorter(stats, A, partitionPoint + 1, high);
    }
}

void quick_sort(Stats *stats, uint32_t *A, int lengthOfArray) {
    quick_sorter(stats, A, 1, lengthOfArray);
}
