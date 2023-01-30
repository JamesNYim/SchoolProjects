//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 3
// GraphTest.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



/*

//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);


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

   return(0);
}

*/
