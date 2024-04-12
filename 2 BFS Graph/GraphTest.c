//Francisco Gomez 				Cruz id: 1775128 			date: 1/23/21
//This is a very simple test inspired by the original GraphClient.c. As long as I was able to track 
//the good use of the graph.c basic functionality, I would only then move on to the test scripts.
//-----------------------------------------------------------------------------
//
// GraphClient.c
//
// This is a fancy test client that calculates the Radius and Diameter of
// the graph defined on lines 41-49, along with its Central and Peripheral
// vertices.  The definitions of these terms at:
//
//    http://en.wikipedia.org/wiki/Distance_(graph_theory)
//
// Place this file in a directory with copies of your List.c, List.h, Graph.c,
// Graph.h and an appropriate Makefile, then compile and run. The output
// is contained in the file GraphClientOut.
//
// This program does not exercise all functions in your Graph ADT, but it
// does a pretty good job of testing BFS().  If your output differs from
// the above, you have a logical problem in either your Graph or List ADT.
//
// Remember you are required to submit a file named GraphTest.c with pa4 that
// exercises your Graph functions.  Do not submit this file.
//
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
    Graph G = newGraph(6);
    addEdge(G, 1,2);
    addEdge(G, 1,3);
    addEdge(G,2,4);
    addEdge(G, 2,5);
    addEdge(G, 2, 6);addEdge(G, 3, 4);
    addEdge(G, 4,5);
    addEdge(G, 5, 6);


    BFS(G, 2);

    if (getOrder(G) != 6){
        return 1;
    }

    if (getSize(G) != 8){
        return 1;
    }

    if (getSource(G) != 2){
        return 1;
    }

    List path_test = newList();
    getPath(path_test, G, 3);
    printGraph(stdout, G);
    printList(stdout, path_test);
    makeNull(G);
    freeList(&path_test);
    freeGraph(&G);

    //so far everything works, it would be time to use the test scripts

    return 0;
}