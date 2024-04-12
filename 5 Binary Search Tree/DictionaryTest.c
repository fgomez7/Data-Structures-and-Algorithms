//-----------------------------------------------------------------------------
//Francisco Gomez       Cruz id: 1775128        Feb 19, 2021
//test out all of the functions of Dictionary.c to make sure the program would run properly
// DictionaryClient.c
// Test client for Dictionary ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"
int main() {

    int i, n = 26;
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);
    char* word[] = { "n","z","w","k","i","c","l","d","t","a"};

    VAL_TYPE x;
    VAL_TYPE y;

    for(i=0; i<n; i++){
        insert(A, word[i], i);
    }

    for(i=0; i<n; i+=2){
        delete(A, word[i]);
    }

    beginForward(A);
    printf("%s %d\n", currentKey(A), currentVal(A));

    printDictionary(stdout, A);

    printf("This is the size: %d. And this is the unique key: %d", size(A), getUnique(B));

    freeDictionary(&A);
    freeDictionary(&B);

    return 0;
}
