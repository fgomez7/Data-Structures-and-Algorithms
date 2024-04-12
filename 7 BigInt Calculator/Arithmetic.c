//Francisco Gomez       Cruz id: 1775128        Sat March 12, 2021
//Calculates the outcome of basic arithmetic operations that consist of
//numbers that are generally too large to compute without the help of helper
//functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInteger.h"
#define MAX_LEN 300

int main(int argc, char* argv[]) {
    //234 345 234 4 583 484
    //char line[MAX_LEN];
//    char* number = NULL;
//    char* number2 = NULL;
    //int line_count = 0;

    int number_1, number_2;

    FILE *in, *out;
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    BigInteger A = newBigInteger();
    BigInteger B = newBigInteger();

//    while ( fgets( line, MAX_LEN, in ) != NULL ){
//        line_count ++;
//        if (line_count == 1){
//            number = strtok( line, "\n" );
//            number_1 = atoi(number);
//        }
//        if (line_count == 3){
//            number = strtok(line, "\n");
//            number_2 = atoi(number);
//        }
//    }
//    rewind(in);
//    if ( number_1 > number_2 ){
//        max = number_1;
//    }else{
//        max = number_2;
//    }
//    char line_2[max+2];
//    line_count = 0;
//    while ( ( fgets( line_2, max+2, in) != NULL )){
//        line_count++;
//        if (line_count == 2){
//            number = strtok(line_2, "\n");
//            A = stringToBigInteger(number);
//        }
//        if (line_count == 4){
//            number = strtok(line_2, "\n");
//            B = stringToBigInteger(number);
//        }
//    }

    fscanf(in, " %d\n", &number_1);
    char number[number_1];
    fscanf(in, " %s", number);
    A = stringToBigInteger(number);
    fscanf(in, " %d\n", &number_2);
    char number2[number_2];
    fscanf(in, " %s", number2);
    B = stringToBigInteger(number2);


    printBigInteger(out, A);

    printBigInteger(out, B);
    BigInteger Result_2 = newBigInteger();
    BigInteger Result_3 = newBigInteger();
    BigInteger Result = sum(A, B);      printBigInteger(out, Result);
    subtract(Result, A, B);             printBigInteger(out, Result);
    subtract(Result, A, A);             printBigInteger(out, Result);
    BigInteger ThreeA = stringToBigInteger("0003");
    multiply(Result, A, ThreeA);        //printBigInteger(out, Result);
    BigInteger TwoB = stringToBigInteger("00002");
    Result_2 = prod(B, TwoB);
    Result_3 = diff(Result, Result_2);  printBigInteger(out, Result_3);
    multiply(Result, A, B);             printBigInteger(out, Result);

    multiply(Result, A, A);             printBigInteger(out, Result);
    multiply(Result_2, B, B);             printBigInteger(out, Result_2);


    BigInteger NineA = stringToBigInteger("0009");
    multiply(Result_3, Result, Result);
    BigInteger X = prod(Result_3, NineA);

    BigInteger SixTeenB = stringToBigInteger("00016");
    multiply(Result, Result_2, Result_2);       multiply(Result_2, Result, B);
    BigInteger Y = prod(Result_2, SixTeenB);

    add(Result, X, Y);      printBigInteger(out, Result);

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&Result);
    freeBigInteger(&Result_2);
    freeBigInteger(&Result_3);
    freeBigInteger(&X);
    freeBigInteger(&Y);
    fclose(in);
    fclose(out);

    //A, B, A + B, A - B, A - A, 3A - 2B, AB, A^2, B^2, 9A^4 + 16B^5
    //01 72 17 20 54 96 52 35 50 74 89 02 93 69 16 68 81 13 19 54 97 09 03 22 57 21

    return 0;
}
