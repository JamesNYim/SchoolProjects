# Assignment 2: Numerical Integration (README.md)

## Short description:
This program has its own math library (mathlib.c) and uses this math library to perform integrals using Simpsons 1/3. It is able to choose from a selection of functions and integrate these functions based upon user input. The user is able to input which function to integrate, the lower bounds, the upper bounds, and the amount of partitions. It will then run and return a list of integrals based on the amount of partitions.

## Build
	To build manually, type "clang -Wall -Wextra -Werror -Wpedantic -o integrate integrate.c" on the command line
	Alternatively, type "make" on the command line with the Makefile provided in the directory

## Running
	./integrate(-functionOption, -lowerBound, -upperBound, -numberOfPartitions)

## Cleaning
	To clean manually, type "rm -f integrate integrate.o" on the command line
	Alternatively type "clean" on the command line, using Makefile provided

## Errors:
	When running ./integrate with no arguments you will not get any output. The program will just exit. To fix just input options. (see ./integrate -H) When running with an illegal option the program will output an error message. To fix just input legal options. (see ./integrate -H)


























































