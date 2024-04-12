//-----------------------------------------------------------------------------
// Francisco Gomez      Cruz id: 1775128        Feb 7, 2021
// Shuffle.cpp: the main file of this assignment which calculates the permutations
//during perfect shuffles of any size deck
//-----------------------------------------------------------------------------
#include<iostream>
#include <stdio.h>
#include<string>
#include"List.h"

using namespace std;

int main(int argc, char* argv[]){

    if ( argc != 2 ){
        exit(1);
    }
    printf("deck size       shuffle count\n");
    printf("------------------------------\n");
    int deck_size = atoi(argv[1]);
    List Deck_1, Deck_2, Shuffled, Original;
    int split, permutation = 0, counter = 0;
    for (int i = 1; i <= deck_size ; i++) {
        if (i == 1){
            printf(" 1               1\n");
            continue;
        }

        split = i/2;

        //List Deck_1, Deck_2, Shuffled, Original;
        for (int j = 0; j < split; j++) {
            Deck_1.insertBefore(j);
            Original.insertBefore(j);
        }
        for (int j = split; j < i; j++) {
            Deck_2.insertBefore(j);
            Original.insertBefore(j);
        }
        Deck_1.moveFront();
        while (!Original.equals(Shuffled)){
            for (Deck_2.moveFront(); Deck_2.peekNext() != -1 ; Deck_2.moveNext()) {

                Shuffled.insertBefore(Deck_2.peekNext());
                if (Deck_1.peekNext() == -1){
                    break;
                }
                Shuffled.insertBefore(Deck_1.peekNext());

                Deck_1.moveNext();
            }
            permutation ++;
            if (Original.equals(Shuffled)){
                break;
            }
            Deck_1.clear(); Deck_2.clear();
            for (Shuffled.moveFront(); Shuffled.peekNext() != -1; Shuffled.moveNext()) {
                if (counter < split){
                    Deck_1.insertBefore(Shuffled.peekNext());
                    counter++;
                }
                else{
                    Deck_2.insertBefore(Shuffled.peekNext());
                }
            }
            counter = 0; Shuffled.clear(); Deck_1.moveFront();
        }
        printf(" %d               %d\n", i, permutation);
        Deck_1.clear(); Deck_2.clear(); Original.clear(); Shuffled.clear();
        permutation = 0; counter = 0;
    }


    return(0);
}