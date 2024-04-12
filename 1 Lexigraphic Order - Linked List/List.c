//Francisco Gomez      cruz id: 1775128     date: 1/16/2021
//Linked with List.h and includes all the functions which allows the program to make a doubly linked list and modify 
//the list by appending nodes onto the list as well as an implementation of a cursor in the list
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//structs
typedef struct NodeObj{
    int data;
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
Node newNode(int data){
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
        exit(EXIT_FAILURE);
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
int front(List L){// Returns front element of L. Pre: length()>0
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
int back(List L) { // Returns back element of L. Pre: length()>0
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
int get(List L) { // Returns cursor element of L. Pre: length()>0, index()>=0
    if (L->length > 0 && L->index >= 0){
        return L->cursor->data;
    }
    return -1;
}
int equals(List A, List B) // Returns true (1) iff Lists A and B are in same
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
void prepend(List L, int x){ // Insert new element into L. If L is non-empty,
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
void append(List L, int x){ // Insert new element into L. If L is non-empty,    //ENQUEUE IS APPEND, REMEMBER THAT!!!
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
void insertBefore(List L, int x) // Insert new element before cursor.
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
void insertAfter(List L, int x) // Insert new element after cursor.
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
        //N->previous = NULL;
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
void printList(FILE* out, List L) // Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
{
    Node N = NULL;
    if (L == NULL){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for (N = L->front;N!=NULL; N = N->next) {
        printf("%d ", N->data);
    }
    printf("\n");
}
List copyList(List L) // Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
{
    List C = newList();
    int x = 0;
    Node N = NULL;
    for (N = L->front; N!=NULL; N=N->next) {
        x = N->data;
        append(C, x);
    }

    return C;
}
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