/*
Francisco Gomez, Cruz id: 1775128 date: Sunday January 31, 2021
graph.c is the implementation for the function of dfs which is different than bfs
*/
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

typedef struct GraphObj{
    List *adj;
    int *color;
    int *discovered_time;
    int *finished_time;
    int *parent;
    int order;
    int size;
    int time;
    List stack;
}GraphObj;

// Constructors-Destructors
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adj = malloc((n+1) * sizeof(List));
    G->color = malloc((n+1)*sizeof(int));
    G->discovered_time = malloc((n+1) * sizeof(int));
    G->finished_time = malloc((n+1) * sizeof(int));
    G->parent = malloc((n+1) * sizeof(int));
    G->stack = newList();
    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i]= NIL;
        G->discovered_time[i] = UNDEF;
        G->finished_time[i] = UNDEF;
    }
    G->order = n;
    G->size = 0;
    G->time = NIL;
    return G;
}
void freeGraph(Graph* pG){
    if (pG != NULL && *pG != NULL){
        for (int i = 1; i <= (*pG)->order; i++) {
            freeList(&(*pG)->adj[i]);
        }
        freeList(&(*pG)->stack);
        free((*pG)->adj);
        free((*pG)->finished_time);
        free((*pG)->discovered_time);
        free((*pG)->parent);
        free((*pG)->color);
        free((*pG)->stack);
        free((*pG));
        *pG = NULL;
    }
}
// Access functions
int getOrder(Graph G){
    return G->order;
}
int getSize(Graph G){
    return G->size;
}
int getParent(Graph G, int u){ /* Pre: 1<=u<=n=getOrder(G) */
    int n = getOrder(G);
    if (u >= 1 && u <= n){
        /*if (G->parent[u] == NIL){
            return 0;
        }*/
        return G->parent[u];
    }
    return -1;
}
int getDiscover(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */ {
    int n = getOrder(G);
    if (u >= 1 && u <= n){
        return G->discovered_time[u];
    }
    printf("Did not meet the preconditions");
    exit(EXIT_FAILURE);
}
int getFinish(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */{
    int n = getOrder(G);
    if (u >= 1 && u <= n){
        return G->finished_time[u];
    }
    printf("Did not meet the preconditions");
    exit(EXIT_FAILURE);
}
// Manipulation procedures
void addArc(Graph G, int u, int v) /* Pre: 1<=u<=n, 1<=v<=n */{
    int n = getOrder(G);
    if (u >= 1 && u <= n && v >= 1 && v <= n){
        if (isEmpty(G->adj[u]) == 1){
            append(G->adj[u], v);
        }
        else if (v < front(G->adj[u])){
            moveFront(G->adj[u]);
            insertBefore(G->adj[u], v);
        }
        else if (v > back(G->adj[u])){
            moveBack(G->adj[u]);
            insertAfter(G->adj[u], v);
        }
        else if (length(G->adj[u]) == 2){
            moveFront(G->adj[u]);
            insertAfter(G->adj[u], v);
        }
        else{
            for (moveFront(G->adj[u]);index(G->adj[u]) >= 0; moveNext(G->adj[u])) {
                if (v < get(G->adj[u])){
                    insertBefore(G->adj[u], v);
                    break;
                }
            }
        }
        G->size ++;
        return;
    }
    printf("Did not meet the preconditions");
    exit(EXIT_FAILURE);
}
void addEdge(Graph G, int u, int v) /* Pre: 1<=u<=n, 1<=v<=n */{
    int n = getOrder(G);
    if (u >= 1 && u <= n && v >= 1 && v <= n){
        if (isEmpty(G->adj[u]) == 1){
            append(G->adj[u], v);
        }
        else if (v < front(G->adj[u])){
            moveFront(G->adj[u]);
            insertBefore(G->adj[u], v);
        }
        else if (v > back(G->adj[u])){
            moveBack(G->adj[u]);
            insertAfter(G->adj[u], v);
        }
        else if (length(G->adj[u]) == 2){
            moveFront(G->adj[u]);
            insertAfter(G->adj[u], v);
        }
        else{
            for (moveFront(G->adj[u]);index(G->adj[u]) >= 0; moveNext(G->adj[u])) {
                if (v < get(G->adj[u])){
                    insertBefore(G->adj[u], v);
                    break;
                }
            }
        }
        if (isEmpty(G->adj[v]) == 1){
            append(G->adj[v], u);
        }
        else if (u < front(G->adj[v])){
            moveFront(G->adj[v]);
            insertBefore(G->adj[v], u);
        } else if (u > back(G->adj[v])){
            moveBack(G->adj[v]);
            insertAfter(G->adj[v], u);
        }
        else if (length(G->adj[v]) == 2){
            moveFront(G->adj[v]);
            insertAfter(G->adj[v], u);
        } else{
            for (moveFront(G->adj[v]); index(G->adj[v]) >= 0 ; moveNext(G->adj[v])) {
                if (u < get(G->adj[v])){
                    insertBefore(G->adj[v], u);
                    break;
                }
            }
        }
        //append(G->adj[u], v);
        //append(G->adj[v], u);
        G->size ++;
        return;
    }
    printf("Did not meet the preconditions");
    exit(EXIT_FAILURE);
}
void DFS(Graph G, List S) /* Pre: length(S)==getOrder(G) */{
    //clear(G->stack);
    if (length(S) != getOrder(G)){
        printf("Did not meet the preconditions");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    G->time = 0;
    int x;
    for (moveFront(S); index(S) >= 0; moveNext(S)) {//main loop for DFS
        x = get(S);
        if (G->color[x] == WHITE){
            //moveBack(S);
            Visit(G, x);
        }
    }
    moveFront(S);
    for (moveFront(G->stack); index(G->stack) >= 0; moveNext(G->stack)) {
        set(S, get(G->stack));
        moveNext(S);
    }
    clear(G->stack);

}
void Visit(Graph G, int x){//greatest finished time to least
    if (isEmpty(G->adj[x]) == 1){
        G->discovered_time[x] = G->time += 1;
        G->color[x] = GREY;
        G->finished_time[x] = G->time += 1;
        prepend(G->stack, x);
        return;
    }
    G->discovered_time[x] = G->time += 1;
    G->color[x] = GREY;
    int y;
    for (moveFront(G->adj[x]); index(G->adj[x]) >= 0; moveNext(G->adj[x])){
        y = get(G->adj[x]);
        if (G->color[y] == WHITE){
            G->parent[y] = x;
            Visit(G, y);
        }
    }
    G->color[x] = BLACK;
    prepend(G->stack, x);
    G->finished_time[x] = G->time += 1;
}
// Other Functions
Graph transpose(Graph G){
    Graph New = newGraph(G->order);
    for (int i = 1; i <= G->order; i++) {
        if (isEmpty(G->adj[i]) == 1){
            continue;
        }
        for (moveFront(G->adj[i]); index(G->adj[i]) >= 0 ; moveNext(G->adj[i])) {
            append(New->adj[get(G->adj[i])], i);
        }
    }
    return New;
}
Graph copyGraph(Graph G){
    Graph New = newGraph(G->order);
    for (int i = 1; i <= G->order ; i++) {
        New->adj[i] = copyList(G->adj[i]);
    }
    return New;
}
void printGraph(FILE* out , Graph G){
    for (int i = 1; i <= G->order; i++) {
        if (isEmpty(G->adj[i]) == 1){
            fprintf(out, "%d:",  i);
            fprintf(out, "\n");
            continue;
        }
        fprintf(out, "%d:",  i);
        for (moveFront(G->adj[i]); index(G->adj[i]) >= 0 ; moveNext(G->adj[i])) {
            fprintf(out, " %d", get(G->adj[i]));
        }
        fprintf(out, "\n");
    }
}