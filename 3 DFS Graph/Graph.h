/*
	Francisco Gomez, Cruz id: 1775128 date: Sunday January 31, 2021
	This header file holds the structure to graph.c which is used to implement a 
	dfs search on any type of graph
*/
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include "List.h"
#define NIL -2
#define UNDEF -50
#define WHITE -10
#define GREY -20
#define BLACK -30

typedef struct GraphObj* Graph;
// Constructors-Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);
// Access functions
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
// Manipulation procedures
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
void Visit(Graph G, int x);
// Other Functions
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

#endif
