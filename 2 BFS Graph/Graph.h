//Francisco Gomez 				Cruz id: 1775128 			date: 1/23/21
//This file is pretty much the structure of Graph.c which holds all of its functionality
//I used everything that was including in the pa2 pdf in my .h file but added some other functions of my own
//that would make my life a little easier
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include "List.h"
#define NIL -2
#define INF -50
#define WHITE -10
#define GREY -20
#define BLACK -30

/*** Constructors-Destructors ***/
typedef struct GraphObj* Graph;


Graph newGraph(int n);//returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges

void freeGraph(Graph* pG);//frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL
/*** Access functions ***/

int getOrder(Graph G);//return the corresponding field values

int getSize(Graph G);//return the corresponding field values

int getSource(Graph G);//returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called

void set_source(Graph G, int x);

void sortAdj(Graph G, int x);

int getParent(Graph G, int u);//will return the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if BFS() has not yet been called

int getDist(Graph G, int u);//returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.

void getPath(List L, Graph G, int u);//appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
/*** Manipulation procedures ***/
void makeNull(Graph G);//deletes all edges of G, restoring it to its original (no edge) state. (This is called a null graph in graph theory literature).

void addEdge(Graph G, int u, int v);//inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.

void addArc(Graph G, int u, int v);//inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)

void BFS(Graph G, int s);//runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly.
/*** Other operations ***/
void printGraph(FILE* out, Graph G);//prints the adjacency list representation of G to the file pointed to by out.

#endif