# Assignment 6: Huffman Coding (README.md)

## Short description:
	This program will be able to take in a file, and reduce the size of the file using a conept called Huffman coding. It will also be able to take the compressed file, and decomporess it and output the original file.

## Build
	To build manually type, "clang -Wall -Wextra -Werror -Wpedantic -o  encode encode.o decode decode.o node.o pq.o stack.o code.o io.o huffman.o"
	Alternatively type "make" on the command line with the Makefile provided in the directory.

## Running
	./encode (-encoding options)
	./decode (-decoding options)

## Cleaning
	To clean manually type "rm -f encode encode.o decode decode.o node.o pq.o stack.o code.o io.o huffman.o"
	Alternatively type "clean" on the command line, using Makefile provided

## Errors:
	At this current version encode and decode do not actually work as intended. It is still incomplete. 

## Error Handling:
	At this current version encode and decode do not actually work as intended. 
	If there is another error please check ./encode -h or ./decode -h for usage.













