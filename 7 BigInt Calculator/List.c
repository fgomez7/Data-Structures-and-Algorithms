//Francisco Gomez       Cruz id: 1775128        date: March 13, 2021
//this file is a remnant from the original programming assignment 1
//consists of all the same functions but has multiple helper functions at the bottom
//which are used to improve the performance of BigInteger.c
#include <stdio.h>
#include <stdlib.h>
#define POWER 2
#include "List.h"


//structs
typedef struct NodeObj{
    LIST_ELEMENT data;
    struct NodeObj* next;
    struct NodeObj* previous;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;//points at an node
    int index;//index shows where the curor is
    int length;//<---- i
}ListObj;

// Constructors-Destructors ---------------------------------------------------
//returns a new node
Node newNode(LIST_ELEMENT data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->previous = NULL;
    return (N);
}
//frees the node
void freeNode(Node* pN){
    if (pN != NULL && *pN!=NULL){
        free(*pN);
        *pN = NULL;
    }
}
List newList(void){
    List L = malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->length = 0;//<--- should this be length? instead of length
    L->cursor = NULL;
    L->index = -1;
    return L;
}// Creates and returns a new empty List.
void freeList(List* pL){// Frees all heap memory associated with *pL, and sets          are those the only functions that i need to finish with the list?
    if (pL != NULL && *pL != NULL){
        while (!isEmpty(*pL)){
            deleteBack(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}
// *pL to NULL.
// Access functions -----------------------------------------------------------
int isEmpty (List L){
    if (L == NULL){
        printf("List Error: calling isEmpty() on NULL List reference\n");
        //exit(EXIT_FAILURE);
        return 1;
    }
    return(L->length == 0);
}
int length(List L){ // Returns the number of elements in L.
    if (L==NULL){
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->length);
}
int index(List L){ // Returns index of cursor element if defined, -1 otherwise.             WORK ON PREPEND AND APPEND!!!!!
    if (L==NULL){
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->index);
    //return L->front;//yeah, it checks
}
LIST_ELEMENT front(List L){// Returns front element of L. Pre: length()>0
    if (L == NULL){
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)){
        printf("List Error: calling isEmpty() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);
}
LIST_ELEMENT back(List L) { // Returns back element of L. Pre: length()>0
    if (L == NULL){
        printf("List Error: calling back() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)){
        printf("List Error: calling isEmpty() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}
LIST_ELEMENT get(List L) { // Returns cursor element of L. Pre: length()>0, index()>=0
    if (L->length > 0 && L->index >= 0){
        return L->cursor->data;
    }
    return -1;
}
int equals_list(List A, List B) // Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
{
    int li = 0;
    Node N = NULL;
    Node M = NULL;
    if (A == NULL || B == NULL){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    li = (A->length == B->length);
    N = A->front;
    M = B->front;
    while (li && N != NULL){
        li = (N->data == M->data);
        if ( li == 0 ){
            if (N->data > M->data){
                return 0;
            }
            else{
                return -1;
            }
        }
        N = N->next;
        M = M->next;
    }
    return li;
}
// Manipulation procedures ----------------------------------------------------
void clear(List L) // Resets L to its original empty state.
{
    while (L->back != NULL){
        deleteBack(L);
    }
    //L->front = L->back;
    //freeNode(&L->front);
    //deleteBack(L);
}

void set(List L, int x) { // Overwrites the cursor element’s data with x.
    if (L->length > 0 && L->index >=0){// Pre: length()>0, index()>=0
        L->cursor->data = x;
    }
}
void moveFront(List L) { // If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
    if (L == NULL){
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)){
        printf("List Error: calling isEmpty() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->front;
    L->index = 0;
}
void moveBack(List L) { // If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
    if (L == NULL){
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)){
        printf("List Error: calling isEmpty() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->back;
    L->index = L->length -1;
}
void movePrev(List L) { // If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
    if (L->cursor != NULL && L->cursor != L->front){
        L->cursor = L->cursor->previous;
        L->index --;
    }
    else if (L->cursor != NULL && L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;
    }
}
void moveNext(List L) { // If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
    if (L->cursor != NULL && L->cursor != L->back){
        L->cursor = L->cursor->next;
        L->index++;
    }
    else if (L->cursor != NULL && L->cursor == L->back){
        L->cursor = NULL;
        L->index = -1;
    }
}
void prepend(List L, LIST_ELEMENT x){ // Insert new element into L. If L is non-empty,
    Node N = newNode(x);
    if (L == NULL){
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L) == 1){
        L->front = L->back = N;
    }
    else if (L->index == -1){
        Node S = L->front;
        L->front->previous = N;
        L->front = N;
        L->front->next = S;
    }
    else{
        Node S = L->front;
        L->front->previous = N;
        L->front = N;
        L->front->next = S;
        L->index++;
    }
    L->length++;
}
// insertion takes place before front element.
void append(List L, LIST_ELEMENT x){ // Insert new element into L. If L is non-empty,    //ENQUEUE IS APPEND, REMEMBER THAT!!!
    Node N = newNode(x);
    if (L == NULL){
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)){
        L->front = L->back = N;
    } else{
        Node S = L->back;
        L->back->next = N;
        L->back = N;
        L->back->previous = S;
    }
    L->length++;
}
// insertion takes place after back element.
void insertBefore(List L, LIST_ELEMENT x) // Insert new element before cursor.
// Pre: length()>0, index()>=0
{
    if (L->length > 0 && L->index >= 0){
        if (L->cursor->previous == NULL){
            Node N = newNode(x);
            L->cursor->previous = N;
            N->next = L->cursor;
            N->previous = NULL;
            L->front = N;
            L->index++;
        } else{
            Node N = newNode(x);
            Node previous = L->cursor->previous;
            N->next = L->cursor;
            previous->next = N;
            N->previous = previous;
            L->cursor->previous = N;
            L->index++;
        }
        L->length ++;
    }
}
void insertAfter(List L, LIST_ELEMENT x) // Insert new element after cursor.
// Pre: length()>0, index()>=0
{
    if (L->length > 0 && L->index>=0){
        if (L->cursor->next == NULL){
            Node N = newNode(x);
            L->cursor->next = N;
            N->previous = L->cursor;
            L->back = N;
        } else{
            Node N = newNode(x);
            Node previous = L->cursor;
            N->previous = previous;
            N->next = L->cursor->next;
            previous->next=N;
            N->next->previous = N;
        }

        //L->index++;
    }
    L->length++;
}
void deleteFront(List L){ // Delete the front element. Pre: length()>0
    Node N = NULL;
    if (L==NULL){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)){
        printf("List Error: calling deleteFront on an empty List\n");
        exit(EXIT_FAILURE);
    }
    N = L->front;
    if (length(L) > 1){
        L->front = L->front->next;
        L->front->previous = NULL;
    } else{
        L->front = L->back = NULL;
    }
    if (L->index > -1){
        L->index--;
    }
    L->length--;
    freeNode(&N);
}
void deleteBack(List L){ // Delete the back element. Pre: length()>0
    Node N = NULL;
    if (L==NULL){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    N = L->back;
    if (L->back == L->cursor){
        L->index = -1;
    }
    if (length(L) > 1){
        L->back = L->back->previous;
        L->back->next = NULL;
        N->previous = NULL;
    } else{
        L->back = L->front = NULL;
    }
    L->length--;
    freeNode(&N);
}
void delete(List L) // Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
{
    if (L->length > 0 && L->index>=0){
        if (L->cursor == L->back){
            L->back = L->cursor->previous;
            L->back->next = NULL;
            L->cursor->data = 0;
        }
        else if (L->index == 0){
            L->front = L->cursor->next;
            L->front->previous = NULL;
            L->cursor->data = 0;
        } else{
            Node previous = L->cursor->previous;
            Node next = L->cursor->next;
            previous->next = next;
            next->previous = previous;
            L->cursor->next = NULL;
            L->cursor->previous = NULL;
            L->cursor->data = 0;
        }

        //set previous to the next
        //cursor next set to NULL
        //cursor previous = NULL
        //cursor next to its previous
        freeNode(&L->cursor);
    }
    L->index = -1;
    L->length--;
}
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L, int sign) // Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
{
    Node N = NULL;
    if (L == NULL){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (sign == 0){
        fprintf(out, "0\n");
        return;
    }
    else if (sign == -1){
        fprintf(out, "-%ld", L->front->data);
    }
    else{
        fprintf(out, "%ld", L->front->data);
    }
    for (N = L->front->next;N!=NULL; N = N->next) {
        fprintf(out, "%02ld", N->data);
    }
    fprintf(out, "\n");
    fprintf(out, "\n");
}
List copyList(List L) // Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
{
    List C = newList();
    LIST_ELEMENT x = 0;
    Node N = NULL;
    for (N = L->front; N!=NULL; N=N->next) {
        x = N->data;
        append(C, x);
    }

    return C;
}

void addList(List A, List B, List S){//A has to be the biggest number

    if ( S->length > 0 ){
        clear(S);
    }

    long total;
    Node a;//a is the bigger number
    Node b = B->back; //b is the smallest number
    //Node Cursor = S->back;

    for ( a = A->back; a != NULL; a = a->previous ) {
        total = (a->data) + (b->data);
        prepend(S, total);
        //Cursor = S->front;
        //Cursor = Cursor->previous;
        b = b->previous;
        if (b == NULL){
            for (a = a->previous; a != NULL ; a = a->previous ) {
                prepend(S, a->data);
                //Cursor = S->front;
                //Cursor = Cursor->previous;
            }
            ClearZeros(S);
            return;
        }
    }

    if (b != NULL ){
        for ( b ; b!= NULL ; b = b->previous) {
            prepend(S, b->data);
            //Cursor = S->front;
            //Cursor = Cursor->previous;
        }
    }
    ClearZeros(S);

//    long total;
//     moveBack(B);
//    for (moveBack(A); index(A) >= 0 ; movePrev(A)) {
//        if (movePrev(B) == -1)
//        total = A->cursor->data + B->cursor->data;
//        prepend(S, total);
//        movePrev(B);
//    }
}

void subtractList(List A, List B, List S){

    if (S->length > 0){
        clear(S);
    }

    Node X; Node Y = B->back;
    long total;
    //Node Cursor;


    for ( X = A->back ; X != NULL ; X = X->previous ) {
        total = X->data - Y->data;
        prepend(S, total);
        //Cursor = S->front;
        //Cursor = Cursor->previous;
        Y = Y->previous;
        if ( Y == NULL ) {
            for ( X = X->previous ;  X != NULL ; X = X->previous ) {
                prepend(S, X->data);
                //Cursor = S->front;
                //Cursor = Cursor->previous;
            }
            ClearZeros(S);
            return;
        }
    }
    if ( Y != NULL ){
        for ( Y ; Y != NULL ; Y = Y->previous ) {
            prepend(S, 0-(Y->data));
            //Cursor = S->front;
            //Cursor = Cursor->previous;
        }
    }
    ClearZeros(S);
}


int normalize(List A, long BASE, int sign){
    Node N = NULL;
    long counter = 0;
    if (A->length == 0){
        return sign = 0;
    }

    if (A->front->data < 0){
        for ( N = A->back ; N != NULL ; N = N->previous ) {
            N->data *= -1;
        }
        sign = -1;
    }

    for ( N = A->back ; N != NULL ; N = N->previous ) {
        if (N->data < 0){
            while (N->data < 0){
                N->data += BASE;
                counter --;
            }
            if ( N->previous == NULL ){
                normalize(A, BASE, sign);
            }
            else{
                N->previous->data += counter;
            }
        }
        else if ( N->data >= BASE ){
            while ( N->data >= BASE ){
                N->data -= BASE;
                counter ++;
            }
            if ( N->previous == NULL ){
                prepend(A, counter);
            }
            else{
                N->previous->data += counter;
            }
        }
        counter = 0;
    }
    ClearZeros(A);
    return sign;
}

void MultiplyList(List A, List B, List Product){
    Node X = A->back;
    Node Y;


    if ( Product->length > 0 ){
        clear(Product);
    }

    Node Cursor = Product->back;
    Node Tracker = Cursor;

    for ( Y = B->back ; Y != NULL ; Y = Y->previous ) {
        for ( X = A->back ;  X != NULL ; X = X->previous ) {
            if ( Cursor == NULL ){
                prepend(Product, X->data * Y->data);
                Cursor = Product->front;
                //Tracker = Product->back;
            }
            else if ( Cursor != NULL && Tracker == Product->back ){
                Cursor->data = (X->data * Y->data);
            }
            else{
                Cursor->data += (X->data * Y->data);
            }
            Cursor = Cursor->previous;
        }
        if ( Y == B->back ){
            Tracker = Product->back;
        }
        Cursor = Tracker = Tracker->previous;
    }
}

void CopyList(List A, List X){//list a is the list needed to be copied
    for ( Node Cursor = A->front ; Cursor != NULL ; Cursor = Cursor->next ) {
        append(X, Cursor->data);
    }
}

int ClearZeros( List A ){

    Node X = A->front;
    while ( X != NULL ){
        if (A->front->data != 0){
            return 1;
        }
        if (A->front->data ==  0){
            deleteFront(A);
        }
        X = A->front;
    }
    return 0;

}

char* substring( const char *src, int m, int n ){

    int len = n - m;

    char *dest = (char*)malloc(sizeof(char) * (len + 1));

    for (int i = m; i < n && (*(src + i) != '\0'); i++){
        *dest = *(src + i);
        dest++;
    }
    *dest = '\0';
    return dest - len;

}

/*
 *     Node N = NULL;
    long counter;

    if (A->front->data < 0){
        for ( N = A->back ; N != NULL ; N = N->previous ) {
            N->data *= -1;
        }
        sign = -1;
    }

    for ( N = A->back ; N != NULL ; N = N->previous ) {
        if (N->data < 0){
            N->data += BASE;
            if ( N->previous == NULL ){
                normalize(A, BASE, sign);
            }
            else{
                N->previous->data -= 1;
            }
        }
        else if ( N->data > BASE ){
            N->data -= BASE;
            if ( N->previous == NULL ){
                append(A, 1);
            }
            else{
                N->previous->data += 1;
            }
        }
    }
 */

/*
 * List reverse(List L)
 *      List R = newList();
 *      int x
 *      for (moveFront(L); index(L)>= 0; moveNext(L){
 *          x = get(L);
 *          prepend(R, x);
 *      }
 *      return R;
*/
