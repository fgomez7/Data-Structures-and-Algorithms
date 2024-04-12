//Francisco Gomez       Cruz id: 1775128        Feb 19, 2021
//This file is the black box of the assignment which reads the files from the user and
//spits out another file holding the same contents as the original file in lexicographic order
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX_LEN 300
#include "Dictionary.h"

int main(int argc, char* argv[]) {

    int line_count;
    FILE *in, *out;
    //char line[MAX_LEN];
    char line_2[MAX_LEN];
    //char* token;
    int index_1 = 0;

    if ( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    if (in == NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    Dictionary A = newDictionary(0);
    line_count = 0;

    while (fgets(line_2, MAX_LEN, in) != NULL){
        line_count++;
    }

    index_1 = 0;
    rewind(in);
    //char array[line_count][MAX_LEN];//dynamic array
    //char** array_2; // pointer -> char*  -> char
    //printf("before allocating memory\n");
    char** array_2 = malloc(sizeof(char**) * line_count);
    //printf("after allocating memory\n");
    for (int i = 0; i < line_count; i++) {

//    while (fgets(line_2, MAX_LEN, in) != NULL || index_1 < line_count){
        fgets(line_2, MAX_LEN, in);
        //printf("%s\n", line_2);
        //token = strtok(line_2, "\n");
//        if (line_2 == NULL){
//            array_2[i] = malloc(sizeof(char) * strlen(line_2)+1);
//            strcpy(array_2[i], "");
//            insert(A, array_2[i], index_1);
//            //index_1++;
//            continue;
//        }
        array_2[i] = malloc(sizeof(char*) * strlen(line_2)+1);//sizeof(char) * strlen(token)+1
        strcpy(array_2[i], line_2);
        insert(A, array_2[i], index_1);
        //index_1++;
    }
    //printf("after for loop\n");

//    rewind(in);
//    char array[line_count][MAX_LEN];
//    while (fgets(line_2, MAX_LEN, in) != NULL || index_1 < line_count){
//        token[] = strtok(line_2, "\n");
//        if (token == NULL){
//            strcpy(array[index_1], "");
//            insert(A, array[index_1], index_1);
//            index_1++;
//            continue;
//        }
//        strcpy(array[index_1], token);
//        insert(A, array[index_1], index_1);
//        index_1++;
//    }
    printDictionary(out, A);
    fclose(in);
    fclose(out);
    //printf("after closing files\n");

    freeDictionary(&A);
    for (int i = 0; i < line_count ; i++) {
        free(array_2[i]);
        array_2[i] = NULL;
    }
    free(array_2);
    array_2 = NULL;
    //freeDictionary(&A);
    //printf("after freeing");

    return 0;
}
