#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Graph.h"

int main()
{
	
	//Creating a graph
	Graph g = newGraph(5);

	//Adding an edge
	addEdge(g, 1, 3);
	printGraph(stdout, g);

	//Clearing the graph
	makeNull(g);
	printGraph(stdout, g);

	//Adding Arc
	addArc(g, 4, 2);
	printGraph(stdout, g);

	//freeing Graph
	freeGraph(&g);
	
	//Testing Accessor Functions
	Graph f = newGraph(5);
	List l = newList();
	addEdge(f, 1, 4);
	addEdge(f, 2, 3);
	addEdge(f, 2, 1);
	BFS(f, 1);

	//Getting Order
	printf("getOrder(): %d\n", getOrder(f));

	//Getting Size
	printf("getSize(): %d\n", getSize(f));

	//Getting Source
	printf("getSource(): %d\n", getSource(f));

	//Getting Parent
	printf("getParent(): %d\n", getParent(f, 4));

	//Getting Distance
	printf("getDist(): %d\n", getDist(f, 4));

	//Getting Path
	getPath(l, f, 4);
	printList(stdout, l);
	return 0;
}
