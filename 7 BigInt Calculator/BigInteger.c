//Francisco Gomez       Cruz id: 1775128        Date: March 13, 2021
//consists of functions which convert strings to sub-integers which are manipulated
//and printed to bring out the overall outcome of two really big integers manipulated through
//arithmetic operations
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "BigInteger.h"
#include "List.h"
#define ZERO_STATE 0
#define POS_INTEGER 1
#define NEG_INTEGER -1
#define POWER 2
#define BASE 100

//structs
typedef struct BigIntegerObj{
    List L;
    int sign;
}BigIntegerObj;

BigInteger newBigInteger(){
    BigInteger Big = malloc(sizeof(BigIntegerObj));
    Big->L = newList();
    Big->sign = ZERO_STATE;
    return Big;
}

void freeBigInteger(BigInteger* pN){
    if ( pN != NULL && *pN != NULL ){
        makeZero((*pN));
        free(*pN);
        *pN = NULL;
        pN = NULL;
    }
}

int sign(BigInteger N){
    return N->sign;
}

int compare(BigInteger A, BigInteger B){//ask about compare and what to do if signs are equal
    //check the signs first
    //if they are equal, use for loop to check
    //int number;
    if (A->sign < B->sign){
        return -1;
    }
    else if (A->sign > B->sign){
        return 1;
    }
    else if ( A->sign == POS_INTEGER && B->sign == POS_INTEGER ){
        if ( length(A->L) > length(B->L) ){
            return 1;
        }
        else if ( length(A->L) < length(B->L )){
            return -1;
        }
        else{
            int result = equals_list(A->L, B->L);
            if (result == 0){
                return 1;
            }
            if ( result == -1 ){
                return -1;
            }
        }
    }
    else if ( A->sign == NEG_INTEGER && B->sign == NEG_INTEGER ){
        if ( length(A->L) > length(B->L) ){
            return -1;
        }
        else if ( length(A->L) < length(B->L) ){
            return 1;
        }
        else{
            int result = equals_list(A->L, B->L);
            if (result == 0){
                return -1;
            }
            if ( result == -1 ){
                return 1;
            }
        }
    }
    return 0;

    //return equals(A, B);
}//return 0 if A and B are the same

int equals(BigInteger A, BigInteger B){
    if ( A->L == NULL && B->L == NULL ){
        return 1;
    }
    if ( ( A->L == NULL && isEmpty(B->L) == 1 ) || ( isEmpty(A->L) == 1 && B->L == NULL ) ){
        return 1;
    }
    if ( A->L == NULL || B->L == NULL ){
        return 0;
    }
    int result = equals_list(A->L, B->L);
    if (result != 1){
        return 0;
    }
    if (result == 1 && (B->sign == NEG_INTEGER || A->sign == NEG_INTEGER)){
        if (B->sign == NEG_INTEGER && A->sign == NEG_INTEGER){
            return 1;
        }
        return 0;
    }
    else{
        return 1;
    }
}

void makeZero(BigInteger N){
    freeList(&N->L);
    N->sign = ZERO_STATE;
}

void negate(BigInteger N){
    if ( N->sign == 0 ){
        return;
    }
    N->sign *= NEG_INTEGER;
}

BigInteger stringToBigInteger(char* s){
    BigInteger B = newBigInteger();
    int counter, counter_2, len = POWER;
    int remainder, limit = 0;
    //char number[3] = "";
    int digit = 0;
    long size = strlen(s);
    //long m = atol(char* x)

    if (s[0] == '-'){
        B->sign = NEG_INTEGER;
        limit = 1;
        counter_2 = size;
        counter = counter_2 - len;
    }
    else if ( s[0] == '+'){
        B->sign = POS_INTEGER;
        limit = 1;
        counter_2 = size;
        counter = counter_2 - len;
    }
    else{
        B->sign = POS_INTEGER;
        limit = 0;
        counter_2 = size;
        counter = counter_2 - len;
    }

    for (int j = size; j > limit; j--) {

        char* dest = substring(s, counter, counter_2);
        prepend(B->L, atol(dest));
        remainder = counter;
        counter -= POWER; counter_2 -= POWER;
        //len = counter_2 - counter;
        j = counter_2 + 1;

        if (counter < limit && digit != size){
            counter = limit;
            counter_2 = remainder;
            len = counter_2 - counter;
            j = counter_2 + 1;
            digit = size;
        }
        free(dest);
    }

    if (ClearZeros(B->L) == 0){
        B->sign = ZERO_STATE;
    }
    return B;
    //check the list for the node if it has 0 or if it is empty
    //then i would set the sign to ZERO STATE
}

BigInteger copy(BigInteger N){
    BigInteger Copy = newBigInteger();
    CopyList( N->L, Copy->L );
    Copy->sign = N->sign;
    return Copy;
}

void add(BigInteger S, BigInteger A, BigInteger B){//add calls sum
    //char result;

    if (A->sign == POS_INTEGER && B->sign == POS_INTEGER){
        addList(A->L, B->L, S->L);
        S->sign = normalize(S->L, BASE, 1);
        //add(S, A, B);
    }
    else if ( A->sign == POS_INTEGER && B->sign == NEG_INTEGER){
        subtractList( A->L, B->L, S->L);
        S->sign = normalize( S->L, BASE, 1);
    }
    else if ( A->sign == NEG_INTEGER && B->sign == POS_INTEGER ){
        subtractList( A->L, B->L, S->L);
        S->sign = normalize( S->L, BASE, 1);
        S->sign *= -1;
    }
    else{//neg neg
        addList(A->L, B->L, S->L);
        S->sign = normalize(S->L, BASE, 1);
        S->sign *= -1;
    }

//    if ( ClearZeros(S->L) == 0 ){
//        S->sign = ZERO_STATE;
//    }


//    if (A->sign == NEG_INTEGER) {
//        subtractList(A->L, B->L, S->L);
//    }
//    else{
//        addList(A->L, B->L, S->L);
//    }
    //addList(A->L, B->L, S->L);
}

BigInteger sum(BigInteger A, BigInteger B){
    BigInteger S = newBigInteger();
    add(S, A, B);
    return S;
}

void subtract(BigInteger D, BigInteger A, BigInteger B){
    if (A->sign == POS_INTEGER && B->sign == POS_INTEGER){
        subtractList( A->L, B->L, D->L);
        D->sign = normalize( D->L, BASE, 1);
    }
    else if ( A->sign == POS_INTEGER && B->sign == NEG_INTEGER){
        addList(A->L, B->L, D->L);
        D->sign = normalize(D->L, BASE, 1);
    }
    else if ( A->sign == NEG_INTEGER && B->sign == POS_INTEGER ){
        addList(A->L, B->L, D->L);
        D->sign = normalize(D->L, BASE, 1);
        D->sign *= -1;
    }
    else {//neg neg
        subtractList( A->L, B->L, D->L);
        D->sign = normalize( D->L, BASE, 1);
        D->sign *= -1;
    }

//    if ( ClearZeros( D->L ) == 0 ){
//        D->sign = ZERO_STATE;
//    }
}

BigInteger diff(BigInteger A, BigInteger B){
    BigInteger S = newBigInteger();
    subtract(S, A, B);
    return S;
}

void multiply(BigInteger P, BigInteger A, BigInteger B){

    if ( A->sign == 0 || B->sign == 0 ){
        makeZero(P);
        return;
    }

    MultiplyList(A->L, B->L, P->L);
    normalize(P->L, BASE, 1);
    if ( A->sign == -1 && B->sign == -1 ){
        P->sign = POS_INTEGER;
    }
    else if ( A->sign == -1 || B->sign == -1 ){
        P->sign = NEG_INTEGER;
    }
    else{
        P->sign = 1;
    }
}

BigInteger prod(BigInteger A, BigInteger B){
    BigInteger S = newBigInteger();
    multiply(S, A, B);
    return S;
}

void printBigInteger(FILE* out, BigInteger N){
    printList(out, N->L, N->sign);
}
