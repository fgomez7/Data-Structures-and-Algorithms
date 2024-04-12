#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInteger.h"
#define MAX_LEN 300

int main() {

    BigInteger A;
    char number[] = "-7402779357";//size is == 10
    char number_2[] = "0041085449";

    A = stringToBigInteger(number);
    BigInteger B = stringToBigInteger(number_2);
    BigInteger C = sum(A, B);
    printBigInteger(stdout, C);
    BigInteger D = diff(A, B);
    printBigInteger(stdout, D);
    BigInteger X = prod(A, B);
    printBigInteger(stdout, X);
    BigInteger Copy = copy(A);
    if (!equals(Copy, A)){
        return 1;
    }
    negate(B);
    if (sign(B) != -1){
        return 1;
    }
    int result = compare(A, B);
    if ( result != -1 ){
        return 1;
    }

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&X);
    freeBigInteger(&Copy);

    return 0;
}
