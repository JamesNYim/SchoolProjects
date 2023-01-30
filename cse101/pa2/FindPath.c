#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "Graph.h"


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "ERROR: not enough arguments please try again\n");
		exit(EXIT_FAILURE);
	}

	FILE *inFile;
	FILE *outFile;
	
	//Opening Files
	inFile = fopen(argv[1], "r");
	outFile = fopen(argv[2], "w");

	if (inFile == NULL)
	{
		fprintf(stderr, "Unable to open [%s] for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if (outFile == NULL)
	{
		fprintf(stderr, "Unable to open [%s] for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	return 0;
}
