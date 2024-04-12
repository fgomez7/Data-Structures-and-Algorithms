//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT which test the basic functions of List.h and List.cpp 
//which is pretty similar to the List.c from the first assignment
//-----------------------------------------------------------------------------
#include<string>
#include<iostream>
#include"List.h"

using namespace std;

int main(){

    List A, B;
    for (int i = 1; i <= 10; ++i) {
        A.insertAfter(i);
        B.insertBefore(i);
    }
    //List B = List(A);
    //List C = A;

    B.moveFront();
    A.moveBack();

    //int find_test = A.findPrev(5);

    for (int i = 0; i <=5 ; ++i) {
        B.moveNext();
        A.movePrev();
    }

    int i = 5;
    for (A.moveFront(); A.peekNext() != -1; A.moveNext()) {
        if (A.peekNext() == 5){
            A.insertBefore(i);
            break;
        }
    }
    A.cleanup();
    A.size();
    //A.clear();

    List C = A.concat(B);;

    A.moveFront();
    A.eraseAfter();
    A.eraseBefore();

    C = A;

    C.findPrev(1);
    A.findNext(1);

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << endl;

    cout << "A==A is " << (A==A?"true":"false") << endl;
    cout << "A==B is " << (A==B?"true":"false") << endl;
    cout << "A==C is " << (A==C?"true":"false") << endl;
    cout << endl;

    return(0);
}