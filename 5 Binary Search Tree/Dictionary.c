//Francisco Gomez       Cruz id: 1775128        Feb 19, 2021
//this file holds the implemented portion of Dictionary.h that was provided. It holds functions which help traverse
//the binary search tree implementation as well as helper functions to insert and delete nodes within the tree
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Dictionary.h"
//same key value would go to the right

typedef struct NodeObj{
    KEY_TYPE key;
    VAL_TYPE value;
    struct NodeObj* parent;
    struct NodeObj* left;
    struct NodeObj* right;
}NodeObj;

typedef NodeObj* Node;

typedef struct DictionaryObj{//include elements and cursor and dummy node
    int size;
    int unique_key;
    //int elements;
    Node Root;
    Node Dummy;
    Node Cursor;
}DictionaryObj;

Node newNode (KEY_TYPE key, VAL_TYPE value){//add 2 data fields
    Node N = malloc(sizeof(NodeObj));
    N->key = key;
    N->value = value;
    N->parent = NULL;
    N->left = NULL;
    N->right = NULL;
    return (N);
}

void freeNode(Node* pN){
    if (pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

Dictionary newDictionary(int unique){
    Dictionary D = malloc(sizeof(DictionaryObj));
    D->Dummy = newNode(KEY_UNDEF, 0);
    //D->Dummy->parent = (struct NodeObj *) NIL;
    D->Root = D->Dummy;
    D->Cursor = D->Dummy;
    D->size = 0;
    D->unique_key = unique;//1 is true so we'll have unique keys
    return D;
}

void freeDictionary(Dictionary* pD){//don't free a node pointer
    if (pD != NULL && *pD != NULL){
        makeEmpty(*pD);
        //freeNode(&(*pD)->Cursor);
        freeNode(&(*pD)->Dummy);
        free(*pD);
        //freeNode(&(*pD)->Cursor);
        *pD = NULL;
    }

    //makeEmpty(&D);
    //freeNode *pD;
    //*pD = NULL;
    //succesor and predecessor = next and previous
}

int size(Dictionary D){
    return D->size;
}

int getUnique(Dictionary D){
    return D->unique_key == 1;
}

VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
    if (D == NULL) {
        exit(EXIT_FAILURE);
    }
    if (D->size == 0){
        return VAL_UNDEF;
    }
    D->Cursor = D->Root;
    if (KEY_CMP(k, D->Cursor->key) > 0){
        while (D->Cursor != D->Dummy){
            if (KEY_CMP(k, D->Cursor->key) == 0){
                return D->Cursor->value;
            }
            next(D);
        }
        return VAL_UNDEF;
    } else if (KEY_CMP(k, D->Cursor->key) < 0){
        while (D->Cursor != D->Dummy){
            if (KEY_CMP(k, D->Cursor->key) == 0){
                return D->Cursor->value;
            }
            prev(D);
        }
        return VAL_UNDEF;
    }
    else{
        return D->Cursor->value;
    }
}
//NIL is == the dummy node
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){

    if (D->unique_key == 1){
        Node cursor_2 = D->Cursor;
        if (lookup(D, k) != VAL_UNDEF){
            printf("Dictionary error, cannot insert duplicate keys");
            exit(EXIT_FAILURE);
        }
        D->Cursor = cursor_2;
    }

    Node y =  D->Dummy;
    Node x =  D->Root;
    int comparison;

    Node New = newNode(k, v);
    New->left = D->Dummy;
    New->right = D->Dummy;

    while (x != D->Dummy){
        y = x;
        if ((comparison = KEY_CMP(k, x->key)) < 0){
            x = x->left;
        }
        else {
            x = x->right;
        }
//        else if (KEY_CMP(k, x->key) == 0){
//            if (D->unique_key == 1){
//                printf("Dictionary error, cannot insert duplicate keys");
//                exit(EXIT_FAILURE);
//            }
//            x = x->right;
//        }
    }
    New->parent = y;
    if (y == D->Dummy){
        D->Root = New;
        D->size++;
    }
    else if (KEY_CMP(New->key, y->key) < 0){
        y->left = New;
        D->size++;
    }
    else{
        y->right = New;
        D->size++;
    }
}

void transplant(Dictionary D, Node u, Node v){
    if (u->parent == D->Dummy){
        D->Root = v;
        D->Cursor = v;
    }
    else if (u == u->parent->left){
        u->parent->left = v;
        D->Cursor = v;
    }
    else{
        u->parent->right = v;
        D->Cursor = v;
    }
    if (v != D->Dummy){
        v->parent = u->parent;
        //D->Cursor = v;
    }
}

void delete(Dictionary D, KEY_TYPE k){
    if (lookup(D, k) == VAL_UNDEF){
        return;
    }
    Node z = D->Cursor;
    if (z->left == D->Dummy){
        transplant(D, z, z->right);
        //D->Cursor = D->Root;
        freeNode(&z);
        D->size--;
    }
    else if (z->right == D->Dummy){
        transplant(D, z, z->left);
        //D->Cursor = D->Root;
        freeNode(&z);
        D->size--;
    }
    else{
        Node y = z->right;
        while (y->left != D->Dummy){
            y = y->left;
        }
        if (y->parent != z){
            transplant(D, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(D, z, y);
        y->left = z->left;
        y->left->parent = y;
        //D->Cursor = D->Root;
        beginReverse(D);
        freeNode(&z);
        D->size--;
    }
    //delete(D, k);
}

void makeEmpty(Dictionary D){
    if (D->size == 0){
        //D->Cursor = D->Root;
        return;
    }
    beginReverse(D);
    while (D->size > 1){
        delete(D, D->Cursor->key);
        beginReverse(D);
    }
    delete(D, D->Root->key);
    //D->Root = D->Dummy;
    //free(&(D->Cursor));
    D->Cursor = D->Root;
    //D->size--;
//    while (D->Cursor->right != D->Dummy){
//        delete(D, D->Cursor->right->key);
//    }
//    D->Cursor = D->Root;
//    while (D->Cursor->left != D->Dummy){
//        delete(D, D->Cursor->left->key);
//    }
//    D->Root = D->Dummy;
//    D->Cursor = D->Root;
//    D->Root->key = KEY_UNDEF;
//    D->Root->value = VAL_UNDEF;
//    D->size--;
//    D->Root->right = D->Dummy;
//    D->Root->left = D->Dummy;
//    D->Root->value = 0;
//    D->Root->key = KEY_UNDEF;
}

//TreeMinimum(x) Pre: x != NIL
//while x.left != NIL
//        x = x.left
//return x

VAL_TYPE beginForward(Dictionary D){
    if (D->size == 0){
        return VAL_UNDEF;
    }
    D->Cursor = D->Root;
    while (D->Cursor->left != D->Dummy){
        D->Cursor = D->Cursor->left;
    }
    return D->Cursor->value;
}

VAL_TYPE beginReverse(Dictionary D){
    if (D->size == 0){
        return VAL_UNDEF;
    }
    D->Cursor = D->Root;
    while (D->Cursor->right != D->Dummy){
        D->Cursor = D->Cursor->right;
    }
    return D->Cursor->value;
}

KEY_TYPE currentKey(Dictionary D){
    if (D->Cursor == D->Dummy){
        return KEY_UNDEF;
    }
    else{
        return D->Cursor->key;
    }
}


VAL_TYPE currentVal(Dictionary D){
    if (D->Cursor == D->Dummy){
        return VAL_UNDEF;
    }
    else{
        return D->Cursor->value;
    }
}

VAL_TYPE next(Dictionary D){
    if (D->Cursor->right != D->Dummy){
        D->Cursor = D->Cursor->right;
        while (D->Cursor->left != D->Dummy){
            D->Cursor = D->Cursor->left;
        }
        return D->Cursor->value;
    }
    Node y = D->Cursor->parent;
    while (y != D->Dummy && D->Cursor == y->right){
        D->Cursor = y;
        y = y->parent;
    }
    D->Cursor = y;
    if (D->Cursor == D->Dummy){
        return VAL_UNDEF;
    }
    else{
        return D->Cursor->value;
    }
}

VAL_TYPE prev(Dictionary D){
    if (D->Cursor->left != D->Dummy){
        //return tree maximum
        D->Cursor = D->Cursor->left;
        while (D->Cursor->right != D->Dummy){
            D->Cursor = D->Cursor->right;
        }
        return D->Cursor->value;
    }
    Node y = D->Cursor->parent;
    while (y != D->Dummy && D->Cursor == y->left){
        D->Cursor = y;
        y = y->parent;
    }
    D->Cursor = y;
    if (D->Cursor == D->Dummy){
        return VAL_UNDEF;
    }
    else{
        return D->Cursor->value;
    }
}

void printDictionary(FILE* out, Dictionary D){
    for (beginForward(D); D->Cursor != D->Dummy ; next(D)) {
        fprintf(out,"%s", D->Cursor->key);
    }
}
