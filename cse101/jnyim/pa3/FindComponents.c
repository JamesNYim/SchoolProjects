

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 3
// FindComponents.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "List.h"
#include <stdbool.h>

int main(int argc, char **argv)
{
	//Checking if there are enough arguments
	if (argc != 3)
	{
		fprintf(stderr, "ERROR: not enough arguments please try again\n");
		exit(EXIT_FAILURE);
	}

	//File Opening
	FILE *inFile;
	FILE *outFile;

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

	//Getting numOfVerticies
	int numOfVerticies = 0;
	fscanf(inFile, "%d", &numOfVerticies);
	
	//Creating the Graph
	Graph g = newGraph(numOfVerticies);

	//Adding Arcs to the Graph
	int vertex1;
	int vertex2;
	fscanf(inFile, "%d %d", &vertex1, &vertex2);
	while (vertex1 != 0 && vertex2 != 0)
	{
		addArc(g, vertex1, vertex2);
		fscanf(inFile, "%d %d", &vertex1, &vertex2);
	}

	//Printing adjacency list
	fprintf(outFile, "Adjacency list representation of G:\n");
	printGraph(outFile, g);

	//Creating Transposed Graph
	Graph gT = transpose(g);

	//Creating List
	List l = newList();

	//Appending to List
	for (int i = 1; i < getOrder(g) + 1; i++)
	{
		append(l, i);
	}

	//DFS on original graph
	DFS(g, l);

	//DFS on Transpose Graph
	DFS(gT, l);

	//Printing out to outFile
	moveBack(l);
	List printL = newList();
	int numOfSCC = 0;
	
	//Getting num of SCC
	while (index(l) >= 0)
        {
                if (getParent(gT, get(l)) == NIL)
                {
                        numOfSCC++;
                }
                movePrev(l);
        }
	fprintf(outFile, "\nG contains %d strongly connected components:\n", numOfSCC);

	moveBack(l);
	int currentSCC = 0;
	while (index(l) >= 0)
	{
		prepend(printL, get(l));
		if (getParent(gT, get(l)) == NIL)
		{
			currentSCC++;
			fprintf(outFile, "Component %d: ", currentSCC);
			printList(outFile, printL);
			fprintf(outFile, "\n");
			clear(printL);

		}
		movePrev(l);
	}
	return 0;
}

