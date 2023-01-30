# Assignment 4: The Game of Life (README.md)

## Short description:
	This program simulates "The Game Of Life" by John Horton Conway. It takes in a list of alive cells and as generations go on, cells change from being alive or dead based on a set of rules. Rules: Any live cell with two or three neighbors survies. Any dead cell with exactly three live neighbors becomes a live cell. All other cells die.

## Build
	To build manually, type "clang -Wall -Wextra -Werror -Wpedantic -o life life.c universe.c" on the command line
	Alternatively, type "make" on the command line with the Makefile provided in the directory

## Running
	.life -(function options)

## Cleaning
	To clean manually, type "rm -f life life.o universe.o" on the command line
	Alternatively type "clean" on the command line, using Makefile provided

## Errors:
	When running valgrind to test for memory leaks. There will be some due to ncurses library having some.

## Error Handling:
	If a user inputs a file with an out of bounds coordinate, the program will stop and throw an out of bounds error message
	If a user inputs a file with an incorrect format, the program will continue to run.











