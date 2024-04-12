//Francisco Gomez      cruz id: 1775128     date: 1/16/2021
//A main() file which sorts an array of strings in alphabetical order fron one file, (input file) to another (out file)
/****************************************************************************************
*  ListClient.c
*  Test client for List ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"List.h"
#define MAX_LEN 300

int main(int argc, char* argv[]){

    int line_count;
    FILE *in, *out;
    char line[MAX_LEN];
    char line_2[MAX_LEN];
    char* token;
    int index_1 = 0;

    // check command line for correct number of arguments
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

    // read each line of input file, then count and print tokens
    List A = newList();
    line_count = 0;
    while( fgets(line, MAX_LEN, in) != NULL)  {
        //append(A, index_1);
        line_count++;
        //index_1++;
    }
    index_1 = 0;
    //fseek(in, 0, MAX_LEN);
    rewind(in);
    char array[line_count][MAX_LEN];
    while (fgets(line_2, MAX_LEN, in) != NULL){

        token = strtok(line_2, " \n");
        strcpy(array[index_1], token);
        //index_1++;
        while (token!= NULL){
            // get next token
            token = strtok(NULL, " \n");
            if (token != NULL){
                strcat(array[index_1], " ");
                strcat(array[index_1], token);
                //strcat(array[index_1], "\n");
            }

        }
        index_1++;
    }

    int s1 = 0;
    append(A, s1);
    moveFront(A);

    for (int s2 = 1; s2 < index_1; ++s2) {
        s1 = get(A);
        while (strcmp(array[s1], array[s2]) < 0){
            if (strcmp(array[s1], array[s2]) == 0){
                break;
            }
            if (s1 == back(A)){
                insertAfter(A, s2);
                moveFront(A);
                break;
            }
            moveNext(A);
            s1 = get(A);
        }
        if (strcmp(array[s1], array[s2]) == 0){
            insertAfter(A, s2);
            moveFront(A);
            continue;
        }
        if (strcmp(array[s1], array[s2])> 0){
            insertBefore(A, s2);
            moveFront(A);
            continue;
        }
    }

    for (int i = 0; i < index_1; ++i) {
        s1 = get(A);
        fprintf(out, "%s\n", array[s1]);
        moveNext(A);
    }

    // close files
    fclose(in);
    fclose(out);
    freeList(&A);

    return(0);

}

/*
 * strcmp(s1, s2)<0 is true if and only if s1 comes before s2           s1 is smaller than s2
strcmp(s1, s2)>0 is true if and only if s1 comes after s2               s1 is greater than s2
strcmp(s1, s2)==0 is true if and only if s1 is identical to s2
 */