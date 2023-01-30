#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LINE_LENGTH 300

		
		

int main(int argc, char**argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "ERROR: not enough arguments please try again\n");
		exit(EXIT_FAILURE);
	}
	
	int lineCount;
	FILE *inFile;
	FILE *outFile;
	
	//Opening files
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

	//Getting line count
	lineCount = 0;
	char line[MAX_LINE_LENGTH];
	while (fgets(line , MAX_LINE_LENGTH, inFile) != NULL)
	{
		lineCount++;
	}
	printf("LineCount: %d\n", lineCount);
	fseek(inFile, 0, SEEK_SET); // moves cursor back to beginning

	//Allocating memory for string array
	char buffer[MAX_LINE_LENGTH];
	char **stringArray = malloc(lineCount * sizeof(char *)); //check if successfully allocated
	for (int i = 0; i < lineCount; i++)
	{
		fgets(buffer, MAX_LINE_LENGTH, inFile);
		stringArray[i] = malloc(strlen(buffer) * sizeof(char)); //check if successfully allocated
		strncpy(stringArray[i], buffer, strlen(buffer));
	}

	//Putting line indexes in List adt
	List theList = newList();
	for (int currentArrayIndex = 0; currentArrayIndex < lineCount; currentArrayIndex++)
	{
		bool isBefore = false;
		moveFront(theList);
		while (index(theList) >= 0)
		{
			
			int cursorValue = get(theList);
			if (strcmp(stringArray[currentArrayIndex], stringArray[cursorValue]) < 0)
			{
				isBefore = true;
				insertBefore(theList, currentArrayIndex);
				moveBack(theList);
			}
			moveNext(theList);
		}
		if (!isBefore)
		{
			append(theList, currentArrayIndex);
		}

	}
	printList(stdout, theList);
	//prnting organized array
	moveFront(theList);
	for (int i = 0; i < lineCount; i++)
	{

		fprintf(outFile, "%s",stringArray[get(theList)]);
		moveNext(theList);
	}

	//Freeing stuff
	freeList(&theList);
	for (int q = 0; q < lineCount; q++)
	{
		free(stringArray[q]);
	}
	free(stringArray);
	
	//Closing files
	fclose(inFile);
	fclose(outFile);	

	return 0;
}
