//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 3
// Graph.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"

//Defintions

typedef struct GraphObj
{
	bool DFSCalled;
	bool BFSCalled;
	int numOfVerticies;
	int numOfEdges;
	int source;
	List *listOfNeighbors;
	int *arrayOfStates;
	int *arrayOfParents;
	int *arrayOfDistances;
	int *arrayOfDiscoverTimes;
	int *arrayOfFinishTimes;

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
	
	//Checking if DFS was called
	g->DFSCalled = false;

	//Checking if BFS was called
	g->BFSCalled = false;
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

	//Creating array of Discover Times
	g->arrayOfDiscoverTimes = calloc(numOfVerticies + 1, sizeof(int));
	for(int i = 0; i < numOfVerticies + 1; i++)
	{
		g->arrayOfDiscoverTimes[i] = UNDEF;
	}

	//Creating array of Finish Times
	g->arrayOfFinishTimes = calloc(numOfVerticies + 1, sizeof(int));
	for (int i = 0; i < numOfVerticies + 1; i++)
	{
		g->arrayOfFinishTimes[i] = UNDEF;
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
	if (g->BFSCalled || g->DFSCalled)
	{
		return g->arrayOfParents[vertex];
	}
	return NIL;
}

//Getting the discover of a vertex
int getDiscover(Graph g, int vertex)
{
	if (g->DFSCalled && (1 <= vertex) && (vertex <= getOrder(g)))
	{
		return g->arrayOfDiscoverTimes[vertex];
	}
	return UNDEF;
}

//Getting the finish of a vertex
int getFinish(Graph g, int vertex)
{
	if (g->DFSCalled && (1 <= vertex) && (vertex <= getOrder(g)))
        {
                return g->arrayOfFinishTimes[vertex];
        }
	return UNDEF;
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
	g->BFSCalled = true;
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

//Visit helper function
int Visit(Graph g, List l, int vertex, int time)
{

	g->arrayOfDiscoverTimes[vertex] = ++time;
	g->arrayOfStates[vertex] = found;
	moveFront(g->listOfNeighbors[vertex]);
	while (index(g->listOfNeighbors[vertex]) >= 0)
	{
		int adjacentVertex = get(g->listOfNeighbors[vertex]);
		if (g->arrayOfStates[adjacentVertex] == notFound)
		{
			g->arrayOfParents[adjacentVertex] = vertex;
			time = Visit(g, l, adjacentVertex, time);
		}
		moveNext(g->listOfNeighbors[vertex]);
	}
	g->arrayOfStates[vertex] = finished;
	prepend(l, vertex);
	g->arrayOfFinishTimes[vertex] = (++time);
	return time;
}
	


//Depth First Search
void DFS(Graph g, List l)
{

	g->DFSCalled = true;
	List tL = newList();
	//Going through the verticies
	for (int vertex = 1; vertex < getOrder(g) + 1; vertex++)
	{
		g->arrayOfStates[vertex] = notFound;
		g->arrayOfParents[vertex] = NIL;
	}
	int time = 0;
	moveFront(l);
	while (index(l) >= 0)
	{
		int vertex = get(l);
		if (g->arrayOfStates[vertex] == notFound)
		{
			time = Visit(g, tL, vertex, time);
		}
		moveNext(l);
	}

	//returning topological sorted List
	moveFront(tL);
	moveFront(l);
	while(index(tL) >= 0 && index(l) >= 0)
	{
		set(l, get(tL));
		moveNext(l);
		moveNext(tL);
	}

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

//Transposing a Graph
Graph transpose(Graph g)
{
	Graph gTranspose = newGraph(getOrder(g));
	for (int vertex = 1; vertex < getOrder(g) + 1; vertex++)
	{
		moveFront(g->listOfNeighbors[vertex]);
		while (index(g->listOfNeighbors[vertex]) >= 0)
		{
			int adjacentVertex = get(g->listOfNeighbors[vertex]);
			addArc(gTranspose, adjacentVertex, vertex);
			moveNext(g->listOfNeighbors[vertex]);
		}
	}
	return gTranspose;
}


//Copying Graph
Graph copyGraph(Graph g)
{
	Graph gCopy = newGraph(getOrder(g));
	gCopy->numOfVerticies = g->numOfVerticies;
        gCopy->numOfEdges = g->numOfEdges;
	gCopy->source = g->source;
	for (int vertex = 1; vertex < getOrder(g) + 1; vertex++)
	{
		gCopy->listOfNeighbors[vertex] = copyList(g->listOfNeighbors[vertex]);
		gCopy->arrayOfStates[vertex] = g->arrayOfStates[vertex];
		gCopy->arrayOfParents[vertex] = g->arrayOfParents[vertex];
		gCopy->arrayOfDistances[vertex] = g->arrayOfDistances[vertex];
		gCopy->arrayOfDiscoverTimes[vertex] = g->arrayOfDiscoverTimes[vertex];
		gCopy->arrayOfFinishTimes[vertex] = g->arrayOfFinishTimes[vertex];
	}

	return gCopy;
}


		






