/*
Francisco Gomez, Cruz id: 1775128 date: Sunday January 31, 2021

This is the main file which is used to find the path of any graph
which the help of graph.c, and list.c as well as the search function called
DFS
*/
//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"
#include "string.h"
#define MAX_LEN 300


int main(int argc, char* argv[]){
    Graph G; int number_u, number_v;
    Graph T = NULL;

    int line_count = 0, n;
    FILE *in, *out;
    char line_2[MAX_LEN];
    char *token;
    char *number_of_edges;

    List S = newList();

    //------------------------------------------------------------------------------//
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    //------------------------------------------------------------------------------//
    while (fgets(line_2, MAX_LEN, in) != NULL){
        if (line_count == 0){
            number_of_edges = strtok(line_2, " \n");
            n = atoi(number_of_edges);
            G = newGraph(n);
            for (int i = 1; i <= n; i++){
                append(S, i);
            }
            line_count ++;
            continue;
        }
        token = strtok(line_2, " \n");
        number_u = atoi(token);
        while (token != NULL){
            token = strtok(NULL, " \n");
            if (token != NULL){
                number_v = atoi(token);
            }
        }
        if (number_v == 0 && number_u == 0){
            //fprintf(out, "\n");
            break;
        }
        addArc(G, number_u, number_v);
    }
  //------------------------------------------------------------------------------//
    DFS(G, S);
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    T = transpose(G);
    //printGraph(out, T);
    //printList(out, S);
    DFS(T, S);
    //printList(out, S);
    int h, d = 0;
    for (int j = 1; j <= n; j++) {
        h = getParent(T, j);
        if (h == NIL){
            d++;
        }
    }
    fprintf(out, "\n");
    fprintf(out, "G contains %d strongly connected components:\n", d);
    int number = d;
    d = 1;
    //moveBack(S);
    int counter = 1, counter_2 = 0;
    for (moveBack(S); index(S) >= 0; movePrev(S)){
        h = getParent(T, get(S));
        if (h == NIL){
            //counter_2 = counter;
            fprintf(out, "Component %d:", d);
            for (counter = counter; counter > 0 ; moveNext(S)) {
                fprintf(out, " %d", get(S));
                counter--;
            }
            counter = 0;
            moveBack(S);
            while (counter < counter_2){
                movePrev(S);
                counter++;
            }
            counter = 0;
            d++;
            if (d == number+1){
                break;
            }
            fprintf(out, "\n");
        }
        counter ++;
        counter_2 ++;
    }
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);

    return(0);
}

