//Francisco Gomez               Cruz id: 1775128            date: 1/23/21
//This is the main file which allows any user to make a graph. It has other functionalities such as printing the 
//adj of a graph as well as other tweeks of my own that I will explain in the README file
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

typedef struct GraphObj{
    List* adj;
    int* color;
    int* parent;
    int* distance;
    int order;//number of vertices
    int size;//number of edges
    int source;
}GraphObj;


Graph newGraph(int n){
    Graph G =   malloc(sizeof(GraphObj));
    G->adj = malloc((n+1)*sizeof(List));
    G->adj[0] = 0;
    G->parent = calloc((n+1), sizeof(int));
    G->distance = calloc((n+1), sizeof(int));
    G->color = malloc((n+1)*sizeof(int));
    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->order = n;
    G->size = 0;
    G->source = NIL;
    return G;
    //add edge between 1 and 2
    //append(adj[1], 2)
    //append(adj[2], 1)

}

void freeGraph(Graph* pG){
    if (pG != NULL && *pG != NULL){
        //while (!isEmpty_1(*pG)){
        //makeNull(*pG);

        //}
        for (int i = 0; i <= (*pG)->order; ++i) {
            freeList(&(*pG)->adj[i]);

        }
        free((*pG)->adj);
        free((*pG)->parent);
        free((*pG)->color);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}
/*** Access functions ***/

int getOrder(Graph G){
    return G->order;
}
int getSize(Graph G){
    return G->size;
}
int getSource(Graph G){
    return G->source;
}

void set_source(Graph G, int x){
    G->source = x;
}

void sortAdj(Graph G, int x){
    if (isEmpty(G->adj[x]) == 1){
        return;
    }
    int length1 = length(G->adj[x]);
    int sorted_array[length1];

    int data, data_2;
    int counter = 0, counter_2 = 0;
    moveFront(G->adj[x]);
    data = get(G->adj[x]);
    sorted_array[0] = data;
    for (moveNext(G->adj[x]); index(G->adj[x]) >=0 ; moveNext(G->adj[x])) {
        data_2 = get(G->adj[x]);
        while (counter >= 0 && sorted_array[counter] >= data_2){
            sorted_array[counter+1] = sorted_array[counter];
            counter --;
        }
        sorted_array[counter + 1] = data_2;
        counter_2 ++;
        counter = counter_2;
    }
    moveFront(G->adj[x]);
    for (int i = 0; i < length1; i++) {
        set(G->adj[x], sorted_array[i]);
        moveNext(G->adj[x]);
        //printf(" %d", sorted_array[i]);
    }
}

int getParent(Graph G, int u){
    return G->parent[u];
}
int getDist(Graph G, int u){
    return G->distance[u];
}
void getPath(List L, Graph G, int u){//finding the path between s and u
    if (isEmpty(G->adj[G->source])==1){
        append(L, NIL);
        return;
    }
    List Reverse_list = newList();
    //prepend(Reverse_list, u);
    int parent = getParent(G, u);
    if (parent == NIL && u != G->source){
        append(L, INF);
        freeList(&Reverse_list);
        return;
    }
    prepend(Reverse_list, u);
    while (parent != NIL){
        prepend(Reverse_list, parent);
        parent = getParent(G, parent);
    }
    for (moveFront(Reverse_list);index(Reverse_list) >= 0; moveNext(Reverse_list)) {
        parent = get(Reverse_list);
        append(L, parent);
    }
    freeList(&Reverse_list);
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
    for (int i = 1; i < G->order; i++) {
        clear(G->adj[i]);
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
}
void addEdge(Graph G, int u, int v){
    append(G->adj[v], u);
    append(G->adj[u], v);
    G->size++;
}
void addArc(Graph G, int u, int v){//one directional
    append(G->adj[u], v);
    G->size++;
}
void BFS(Graph G, int s){
    G->source = s;
    if (isEmpty(G->adj[s])){
        for (int i = 0; i < G->order; i++) {
            G->color[i] = WHITE;
            G->parent[i] = NIL;
            G->distance[i] = INF;
        }
        return;
    }
    G->color[s] = GREY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Color_reset = newList();
    List Queue = newList();
    int x;
    /*
    for (moveFront(G->adj[s]); index(G->adj[s]) >= 0 ; moveNext(G->adj[s])) {
        append(Queue, get(G->adj[s]));
    }
    */
    append(Queue, s);
    append(Color_reset, s);
    while (isEmpty(Queue)==0){
        x = front(Queue);
        deleteFront(Queue);
        int y;
        for (moveFront(G->adj[x]); index(G->adj[x]) >= 0 ; moveNext(G->adj[x])) {
            y = get(G->adj[x]);
            if (G->color[y] == WHITE){
                G->color[y] = GREY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Queue, y);
                append(Color_reset, y);
            }
        }
        G->color[x] = BLACK;
    }
    freeList(&Queue);
    int z;
    for (moveFront(Color_reset); index(Color_reset) >= 0; moveNext(Color_reset)) {
        z = get(Color_reset);
        G->color[z] = WHITE;
    }
    freeList(&Color_reset);
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    int s = getSource(G);
    int number;
    fprintf(out,"%d:", s);
    if (isEmpty(G->adj[s]) == 1){
        fprintf(out, "\n");
        return;
    }
    for (moveFront(G->adj[s]); index(G->adj[s]) >= 0 ; moveNext(G->adj[s])) {
        number = get(G->adj[s]);
        fprintf(out, " %d", number);
    }
    fprintf(out, "\n");
}