# Assignment 3: Sorting: Putting Your Affairs in Order (README.md)

## Short description:
This program has a four different sorting algorithims to choose from. Insertion, Batcher, Heap, and Quick sorts. In ./sorting we are able to choose which sorting algorithims to use from a set of command line inputs. We are able to print out a set number of sorted elements which we can also change the number in the command line. We are also able to set the array to a seed and how many elements to sort.i

## Build
        To build manually, type "clang -Wall -Wextra -Werror -Wpedantic -o integrate integrate.c" on the command line
        Alternatively, type "make" on the command line with the Makefile provided in the directory

## Running
	./sorting( -sortingOptions, -seed, -sizeOfArray, -elementsToPrint)

## Cleaning
        To clean manually, type "rm -f sorting sorting.o batcher.o insert.o heap.o quick.o stats.o" on the command line
        Alternatively type "clean" on the command line, using Makefile provided

## Errors:
	When running insert sort, the amount of "moves" is off by two moves. For any other input errors please see -H of sorting.


