/*Francisco Gomez, Cruz id: 1775128 date: Sunday January 31, 2021
 * Graph Client.c test all of the main functions in graph.c that I have implemented in order to move onto the
 * grading scripts
 */
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

    addArc(G, 1, 2);
    addArc(G, 1, 5);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 2);
    addArc(G, 3, 4);
    addArc(G, 3, 6);
    addArc(G, 3, 7);
    addArc(G, 3, 8);
    addArc(G, 6, 5);
    addArc(G, 6, 7);
    addEdge(G, 8, 7);
    addArc(G, 8, 4);

    printGraph(stdout, G);
    fprintf(stdout, "The size of the Graph is %d\n", getSize(G));

    DFS(G, S);
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(i=1; i<=n; i++){
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }
    fprintf(stdout, "\nThis is the stack for Graph G: ");
    printList(stdout, S);
    fprintf(stdout, "\n");

    T = transpose(G);
    C = copyGraph(G);
    fprintf(stdout, "\n");
    printGraph(stdout, C);
    fprintf(stdout, "Copy Graph works as it should :)\n");
    printGraph(stdout, T);
    fprintf(stdout, "\n");

    DFS(T, S);
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\nThe stack also printed out what it should as expected");

    freeGraph(&G);
    freeGraph(&C);
    freeGraph(&T);
    freeList(&S);

    return(0);
}

