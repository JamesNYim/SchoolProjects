//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 3
// Graph.h
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#pragma once

#include <stdio.h>
#include "List.h"

#define UNDEF -8008135
#define NIL -88
#define INF -28
#define notFound -420
#define found -69
#define finished -8008
//Struct Definition
typedef struct GraphObj *Graph;

//Constructors & Destructors

//Creating a new Graph
Graph newGraph (int numOfVerticies); 

//Freeing a Graph
void freeGraph(Graph *g);

//Accessor Functions

//Getting the order of the Graph
int getOrder(Graph g);

//Getting the size of the Graph
int getSize(Graph g);

//Getting the source of the Graph
int getSource(Graph g);

//Getting the parent of an element
int getParent(Graph g, int element);

//Getting the Discover Time
int getDiscover(Graph g, int vertex);

//Getting the Finish Time
int getFinish (Graph g, int vertex);

//Getting the distance of an element from the source
int getDist(Graph g, int element);

//Getting the path to an element from the source
void getPath(List l, Graph g, int element);

//Manipulation Functions

//Making a Graph NULL
void makeNull(Graph g);

//Adding an edge from elementX to elementY 
void addEdge(Graph g, int elementX, int elementY);

//Adding an arc from elementX to elementY
void addArc(Graph g, int elementX, int elementY);

//Breadth First Search on Graph from sourceElement
void BFS(Graph g, int sourceElement);

//Depth First Search on Graph 
void DFS(Graph g, List l);

//Other Functions

//Transposing a Graph
Graph transpose(Graph g);

//Copying a Graph
Graph copyGraph(Graph g);

//Printing the Graph
void printGraph(FILE *outFile, Graph g);

