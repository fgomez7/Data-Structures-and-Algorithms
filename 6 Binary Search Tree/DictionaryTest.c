//Francisco Gomez   Cruz id: 1775128    Feb 27, 2021
//DictionaryTest.c bsaically tests the basic functionalities of my Dictionary.c
#include <stdio.h>
#include "Dictionary.h"

int main() {

    Dictionary A = newDictionary(1);

    char* word[] = { "n","z","w","k","i","c","l","d","t","a"};

    int n = 10;
    int* t = &n;
    for (int i = 0; i < n; i++) {
        insert(A, word[i], &i);
    }
    if ( size(A) != 10 ){
        printf("exiting, failure");
        return 0;
    }
    if ( getUnique(A) != 1){
        printf("exiting because of error");
        return 0;
    }
    if ( lookup(A, "n") == 0){
        return 1;
    }
    beginForward(A);
    if (lookup(A, "a") == 0){
        return 1;
    }
    beginReverse(A);
    if (lookup(A, "t") == 0){
        return 1;
    }
    if (KEY_CMP("t", currentKey(A)) != 0){
        return 1;
    }
    if (currentVal(A) == t){
        return 1;
    }
    next(A);
    prev(A);
    if (currentVal(A) == t){
        return 1;
    }
    printDictionary(stdout, A, "in");


    delete(A, "n");//delete 14
    freeDictionary(&A);

    return 0;
}
