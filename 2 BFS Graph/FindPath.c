//Francisco Gomez               Cruz id: 1775128            date: 1/23/21
//This c file is the main file I build to test my graph.c and graph.h to find the path of any graph 
//any user would like. From a connected to a disconnected graph.
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include <string.h>
#define MAX_LEN 300

int main(int argc, char* argv[]){

    FILE *in, *out;
    //int line_count = 0;
    char line_2[MAX_LEN];
    char *token;
    char *number_of_edges;

    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

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


    Graph G; int n, number_u, number_v;
    int index_2 = 0;
    rewind(in);
    while (fgets(line_2, MAX_LEN, in) != NULL){
        if (index_2 == 0){//<-----------------------------counts the first number of infile as the number of edges
            number_of_edges = strtok(line_2, " \n");
            //strcpy(array[index_2], number_of_edges);
            index_2++;
            //continue;
            n = atoi(number_of_edges);
            G = newGraph(n);
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
        addEdge(G, number_u, number_v);
    }
    for (int j = 1; j <= n; ++j) {
        sortAdj(G, j);
        set_source(G, j);
        printGraph(out,G);
    }
    //fprintf(out, "\n");

    for (int i = 1; i <= n; ++i) {
        BFS(G, i);
        //printGraph(out,G);
    }
    index_2 = 0;
    int number_s, distance;
    while (fgets(line_2, MAX_LEN, in) != NULL){
        //fprintf(out, "\n");
        token = strtok(line_2, " \n");
        number_s = atoi(token);
        while (token != NULL){
            token = strtok(NULL, " \n");
            if (token != NULL){
                number_u = atoi(token);
            }
        }
        if (number_s == 0 && number_u == 0){
            break;
        }
        if (index_2 == 0){
            fprintf(out, "\n");
            index_2++;
        } else{
            fprintf(out, "\n");
            fprintf(out, "\n");
        }
        List path = newList();
        //set_source(G, number_s);
        //printf("\n");
        BFS(G, number_s);
        getPath(path, G, number_u);
        if (front(path) == -50 || front(path) != number_s){
            fprintf(out, "The distance from %d to %d is infinity\n", number_s, number_u);
            fprintf(out, "No %d-%d path exists", number_s, number_u);
            freeList(&path);
            continue;
        }
        distance = length(path) - 1;
        fprintf(out, "The distance from %d to %d is %d\n", number_s, number_u, distance);
        fprintf(out, "A shortest %d-%d path is:", number_s, number_u);
        printList(out, path);
        //fprintf(out, "\n");


        freeList(&path);
    }
    freeGraph(&G);

    return(0);
}