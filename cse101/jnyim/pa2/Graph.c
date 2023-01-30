#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"

//Defintions

typedef struct GraphObj
{
	int numOfVerticies;
	int numOfEdges;
	int source;
	List *listOfNeighbors;
	int *arrayOfStates;
	int *arrayOfParents;
	int *arrayOfDistances;

}GraphObj;
//Constructors & Destructors

//Creating a new Graph
Graph newGraph(int numOfVerticies)
{
	//Setting up Graph Container
	Graph g = malloc(sizeof(GraphObj));
	if (g == NULL) //Checking if successfully allocated
	{
		return g;
	}
	
	//Setting number of verticies in Graph
	g->numOfVerticies = numOfVerticies;
	
	//Setting num of edges
	g->numOfEdges = 0;
	
	//Setting source to undefined state
	g->source = NIL; 
	
	//Creating list of Neighbors
	g->listOfNeighbors = calloc(numOfVerticies + 1, sizeof(List));
	for (int i = 0; i < numOfVerticies + 1; i++)
	{
		g->listOfNeighbors[i] = newList();
	}

	//Creating array of States
	g->arrayOfStates = calloc(numOfVerticies + 1, sizeof(int));
	
	//Creating array of Parents
	g->arrayOfParents = calloc(numOfVerticies + 1, sizeof(int));
	for (int i = 0; i < numOfVerticies + 1; i++)
	{
		g->arrayOfParents[i] = NIL;
	}

	//Creating array of distances
	g->arrayOfDistances = calloc(numOfVerticies + 1, sizeof(int));
	for (int i = 0; i < numOfVerticies + 1; i++)
        {
                g->arrayOfDistances[i] = NIL;
        }

	//Checking if arrays were successfully allocated
	if (g->listOfNeighbors == NULL || g->arrayOfStates == NULL || g->arrayOfParents == NULL || g->arrayOfDistances == NULL)
	{
		free(g);
		g = NULL;
	}
	return g;
}

//Freeing a Graph
void freeGraph(Graph *g)
{
	if (g)
	{
		for (int i = 0; i < (*g)->numOfVerticies + 1; i++)
		{
			freeList(&(*g)->listOfNeighbors[i]);
		}
		free((*g)->listOfNeighbors);
		free((*g)->arrayOfStates);
		free((*g)->arrayOfParents);
		free((*g)->arrayOfDistances);
		free(*g);
		g = NULL;
	}
}

//Accessor Functions

//Getting the order of Graph
int getOrder(Graph g)
{
	return g->numOfVerticies;
}

//Getting the size of Graph
int getSize(Graph g)
{
	return g->numOfEdges;
}

//Getting the most recent Source of Graph
int getSource(Graph g)
{
	return g->source;
}

//Getting the parent of a vertex in Graph
int getParent(Graph g, int vertex)
{
	if (g->source != NIL)
	{
		return g->arrayOfParents[vertex];
	}
	return NIL;
}

//Getting the distance of a vertex in Graph
int getDist(Graph g, int vertex)
{
	if (g->source != NIL)
	{
		return g->arrayOfDistances[vertex];
	}
	return INF;
}

//Getting the path 
void getPath(List l, Graph g, int destination)
{
	//pre-Cond
	if (g->source == NIL)
	{
		fprintf(stderr, "PreCondition Error (BFS was not ran) [ADT: Graph] [Function: getPath()]\n");
		exit(EXIT_FAILURE);
	}
	if (destination == g->source)
	{
		append(l, g->source);
	}
	else if (g->arrayOfParents[destination] == NIL)
	{
		append(l, NIL);
	}
	else
	{
		getPath(l, g, g->arrayOfParents[destination]);
		append(l, destination);
	}
}

//Manipulator Functions

//Making the Graph NULL
void makeNull(Graph g)
{
	for (int i = 0; i < g->numOfVerticies + 1; i++)
	{
		clear(g->listOfNeighbors[i]);
	}
	g->numOfEdges = 0;
}
//Helper Sort Function
bool listSort(List l, int x)
{
	moveFront(l);
	while (index(l) >= 0)
	{

		int cursorValue = get(l);
		if (x == cursorValue)
		{
			return false;
		}
		if (x < cursorValue)
		{
			insertBefore(l, x);
			return true;

		}
		moveNext(l);
	}
	append(l, x);
	return true;
}

//Making a new edge (Undirected Graph)
void addEdge(Graph g, int aVertex, int bVertex)
{
	if (listSort(g->listOfNeighbors[aVertex], bVertex) && listSort(g->listOfNeighbors[bVertex], aVertex))
	{
		g->numOfEdges++;
	}
}

//Making a new arc (Directed Graph)
void addArc(Graph g, int aVertex, int bVertex)
{
	if (listSort(g->listOfNeighbors[aVertex], bVertex))
	{
		g->numOfEdges++;
	}
}

//Breadth First Search
void BFS(Graph g, int source)
{
	g->source = source;
	//going through verticies 
	for (int vertex = 1; vertex < getOrder(g) + 1; vertex++)
	{
		g->arrayOfStates[vertex] = notFound;
		g->arrayOfDistances[vertex] = INF;
		g->arrayOfParents[vertex] = NIL;
	}
	g->arrayOfStates[source] = found; //Discovering the source
	g->arrayOfDistances[source] = 0;
	g->arrayOfParents[source] = NIL;
	List queue = newList();
	append(queue, source);
	moveFront(queue);
	while (index(queue) >= 0)
	{
		//Dequeueing
		int vertex = get(queue);
		moveFront(g->listOfNeighbors[vertex]);
		//checking neighbors 
		while (index(g->listOfNeighbors[vertex]) >= 0)
		{
			int adjacentVertex = get(g->listOfNeighbors[vertex]);
			if (g->arrayOfStates[adjacentVertex] == notFound) //adjacentVertex hasnt been found
			{
				g->arrayOfStates[adjacentVertex] = found; //discovering adjVertex
				g->arrayOfDistances[adjacentVertex] = g->arrayOfDistances[vertex] + 1;
				g->arrayOfParents[adjacentVertex] = vertex;

				//Enqueing
				append(queue, adjacentVertex);
			}
			moveNext(g->listOfNeighbors[vertex]);
		}
		g->arrayOfStates[vertex] = finished; //finished looking at vertex
		moveNext(queue);
	}
	freeList(&queue);

}
		
//Other Functions

//Printing a Graph
void printGraph(FILE *outFile, Graph g)
{
	for (int vertex = 1; vertex < g->numOfVerticies + 1; vertex++)
	{
		fprintf(outFile, "%d: ", vertex);
		printList(outFile, g->listOfNeighbors[vertex]);
		fprintf(outFile, "\n");
	}
}







