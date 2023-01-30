#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Help Page
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Sorts an array with various methods chosen by the user..\n"
        "\n"
        "USAGE\n"
        "   %s [-ahbiqrnpH "
        "-a uses all sorting algorithims] [-h uses Heap Sort] [ -b uses Batcher Sort] [-i uses "
        "Insertion Sort] [-r seed: sets a seed. Default is 13371453] [ -n size: sets the array to "
        "size. Default is 100] [-p elements: prints out elements number of elements from the "
        "array. Default is 100. If the size of the array is less than the input the entire array "
        "is printed.] [-H displays the help page]\n"
        "\n"
        "OPTIONS\n"
        "   -a         uses all the sorting algorithims\n"
        "   -h         uses heap sort\n"
        "   -b         uses batcher sort\n"
        "   -i         uses insertion sort\n"
        "   -q         uses quick sort\n"
        "   -r         Sets the seed. Default value is 13371453\n"
        "   -n         Sets the size of array. Default value is 100\n"
        "   -p         Prints the number of elements from the array. Default is 100\n"
        "   -H         Shows the help page\n",
        exec);
}

void arrayGen(uint32_t *A, uint32_t sizeOfArray, uint32_t seed) {
    srandom(seed);
    for (uint32_t i = 0; i < sizeOfArray; i++) {
        A[i] = random() & 0x3FFFFFFF;
    }
}
typedef enum { HEAP, BATCHER, INSERT, QUICK } SortType;

int main(int argc, char **argv) {
    //Variable declaration
    int opt = 0;
    uint32_t sizeOfArray = 100; //default value
    int seed = 13371453; //default value
    uint32_t elementsToPrint = 100; //default value
    Set s = empty_set();
    Stats batcherStats = { 0, 0 };
    Stats insertStats = { 0, 0 };
    Stats heapStats = { 0, 0 };
    Stats quickStats = { 0, 0 };

    //Organizing user input
    while ((opt = getopt(argc, argv, "ahbiqr:n:p:H")) != -1) {
        switch (opt) {
        case 'a': s = complement_set(empty_set()); break;
        case 'h': s = insert_set(HEAP, s); break;
        case 'b': s = insert_set(BATCHER, s); break;
        case 'i': s = insert_set(INSERT, s); break;
        case 'q': s = insert_set(QUICK, s); break;
        case 'r': seed = strtod(optarg, NULL); break;
        case 'n': sizeOfArray = strtod(optarg, NULL); break;
        case 'p': elementsToPrint = strtod(optarg, NULL); break;
        case 'H': usage(argv[0]); return EXIT_FAILURE;
        default: fprintf(stderr, "incorrect usage please see -H for help\n"); return 1;
        }
    }

    //initializing array with malloc
    uint32_t *A = (uint32_t *) malloc(sizeOfArray * sizeof(uint32_t));

    //printing right amount of elements
    if (elementsToPrint > sizeOfArray) {
        elementsToPrint = sizeOfArray;
    }

    //Choosing which sort to use.
    for (SortType sort = HEAP; sort <= QUICK; sort++) {
        if (member_set(sort, s)) {
            switch (sort) {
            case HEAP:
                reset(&heapStats);
                arrayGen(A, sizeOfArray, seed);
                heap_sort(&heapStats, A, sizeOfArray);
                printf("Heap Sort, %d elements, %lu moves, %lu compares", sizeOfArray,
                    heapStats.moves, heapStats.compares);
                for (uint32_t i = 0; i < elementsToPrint; i++) {
                    if ((i % 5) == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
                printf("\n");
                break;

            case INSERT:
                reset(&insertStats);
                arrayGen(A, sizeOfArray, seed);
                insertion_sort(&insertStats, A, sizeOfArray);
                printf("Insert Sort, %d elements, %lu moves, %lu compares", sizeOfArray,
                    insertStats.moves, insertStats.compares);
                for (uint32_t i = 0; i < elementsToPrint; i++) {
                    if ((i % 5) == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
                printf("\n");
                break;

            case BATCHER:
                reset(&batcherStats);
                arrayGen(A, sizeOfArray, seed);
                batcher_sort(&batcherStats, A, sizeOfArray);
                printf("Batcher Sort, %d elements, %lu moves, %lu compares", sizeOfArray,
                    batcherStats.moves, batcherStats.compares);
                for (uint32_t i = 0; i < elementsToPrint; i++) {
                    if ((i % 5) == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
                printf("\n");
                break;

            case QUICK:
                reset(&quickStats);
                arrayGen(A, sizeOfArray, seed);
                quick_sort(&quickStats, A, sizeOfArray);
                printf("Quick Sort, %d elements, %lu moves, %lu compares", sizeOfArray,
                    quickStats.moves, quickStats.compares);
                for (uint32_t i = 0; i < elementsToPrint; i++) {
                    if ((i % 5) == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
                printf("\n");
                break;
            }
        }
    }
    free(A);
    return 0;
}
