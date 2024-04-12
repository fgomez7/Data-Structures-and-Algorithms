//Francisco Gomez   cruz id: 1775128    Feb 27, 2021
//This file contains the brains of Dictionary.c which holds the implementation of a
//red black tree implementation
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Dictionary.h"
#define RED 1
#define BLACK 0

typedef struct NodeObj{
    KEY_TYPE key;
    VAL_TYPE value;
    struct NodeObj* parent;
    struct NodeObj* left;
    struct NodeObj* right;
    int color;  //RED is 1, BLACK is 0
}NodeObj;

typedef  NodeObj* Node;

typedef struct DictionaryObj{
    int size;
    int unique;
    Node Root;
    Node Cursor;
    Node Dummy;
}DictionaryObj;


Node newNode ( KEY_TYPE key, VAL_TYPE value ){
    Node n = malloc(sizeof(struct NodeObj));
    n->key = key;
    n->value = value;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    n->color = BLACK;
    return (n);
}

void freeNode(Node* pN){
    if (pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

Dictionary newDictionary(int unique){
    Dictionary D = malloc(sizeof(DictionaryObj));
    D->Dummy = newNode(KEY_UNDEF, VAL_UNDEF);
    D->Root = D->Dummy;
    D->Cursor = D->Dummy;
    D->size = 0;
    D->unique = unique;
    return (D);
}

void freeDictionary(Dictionary* pD){
    if (pD != NULL &&  *pD != NULL){
        makeEmpty(*pD);
        freeNode(&(*pD)->Dummy);
        free(*pD);
        *pD = NULL;
    }
}

int size(Dictionary D){
    return D->size;
}

int getUnique(Dictionary D){
    return D->unique == 1;
}

Node TreeSearch(Dictionary D, Node x, KEY_TYPE k){
    if (x == D->Dummy || KEY_CMP(k, x->key) == 0){
        return x;
    }
    else if (KEY_CMP(k, x->key) < 0){
        return(TreeSearch(D, x->left, k));
    }
    else{
        return(TreeSearch(D, x->right, k));
    }
}

VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
    Node x = D->Root;
    x = TreeSearch(D, x, k);
    D->Cursor = x;
    if (x == D->Dummy){
        return VAL_UNDEF;
    }
    else{
        return x->value;
    }
//    if (D == NULL) {
//        exit(EXIT_FAILURE);
//    }
//    if (D->size == 0){
//        return VAL_UNDEF;
//    }
//    D->Cursor = D->Root;
//    if (KEY_CMP(k, D->Cursor->key) > 0){
//        while (D->Cursor != D->Dummy){
//            if (KEY_CMP(k, D->Cursor->key) == 0){
//                return D->Cursor->value;
//            }
//            next(D);
//        }
//        return VAL_UNDEF;
//    } else if (KEY_CMP(k, D->Cursor->key) < 0){
//        while (D->Cursor != D->Dummy){
//            if (KEY_CMP(k, D->Cursor->key) == 0){
//                return D->Cursor->value;
//            }
//            prev(D);
//        }
//        return VAL_UNDEF;
//    }
//    else{
//        return D->Cursor->value;
//    }
}

void LeftRotate(Dictionary T, Node x){
    Node y = x->right;
    x->right = y->left;
    if (y->left != T->Dummy){
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == T->Dummy){
        T->Root = y;
    }
    else if (x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RotateRight(Dictionary T, Node x){
    Node y = x->left;
    x->left = y->right;
    if (y->right != T->Dummy){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == T->Dummy){
        T->Root = y;
    }
    else if (x == x->parent->right){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RBInsertFixUp(Dictionary T, Node z){
    Node y;
    while (z->parent->color == RED){
        if (z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if (y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if (z == z->parent->right){
                    z = z->parent;
                    LeftRotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RotateRight(T, z->parent->parent);
            }
        }
        else{
            y = z->parent->parent->left;
            if (y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color =  RED;
                z = z->parent->parent;
            }
            else{
                if (z == z->parent->left){
                    z = z->parent;
                    RotateRight(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(T, z->parent->parent);
            }
        }
    }
    T->Root->color = BLACK;
}

void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
    if (D->unique == 1){
        Node cursor_2 = D->Cursor;
        if (lookup(D, k) != VAL_UNDEF){
            printf("Dictionary error, cannot insert duplicate keys");
            exit(EXIT_FAILURE);
        }
        D->Cursor = cursor_2;
    }

    Node z = newNode(k, v);
    Node y = D->Dummy;
    Node x = D->Root;

    while (x != D->Dummy){
        y = x;
        if (KEY_CMP(z->key, x->key) < 0){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    z->parent = y;
    if (y == D->Dummy){
        D->Root = z;
    }
    else if (KEY_CMP(z->key, y->key) < 0){
        y->left = z;
    }
    else{
        y->right = z;
    }
    z->left = D->Dummy;
    z->right =  D->Dummy;
    z->color = RED;
    RBInsertFixUp(D, z);
    D->size++;
}

void RB_Transplant(Dictionary T, Node u, Node v){
    if (u->parent == T->Dummy){
        T->Root =  v;
    }
    else if ( u == u->parent->left ){
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
    T->Cursor = v;
}

void RB_DeleteFixUp(Dictionary T, Node x){
    Node w;
    while (x != T->Root && x->color == BLACK){
        if (x == x->parent->left){
            w = x->parent->right;
            if (w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(T, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    RotateRight(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(T, x->parent);
                x = T->Root;
            }
        }
        else{
            w = x->parent->left;
            if (w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                RotateRight(T, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK ){
                w->color = RED;
                x = x->parent;
            }
            else{
                if (w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RotateRight(T, x->parent);
                x = T->Root;
            }
        }
    }
    x->color = BLACK;
}

void delete(Dictionary D, KEY_TYPE k){
    if (lookup(D, k) == VAL_UNDEF){
        return;
    }
    Node x;
    Node z = D->Cursor;
    Node y = z;
    int original_color = y->color;
    if (z->left == D->Dummy){
        x = z->right;
        RB_Transplant(D, z, z->right);
        freeNode(&z);
    }
    else if (z->right == D->Dummy){
        x = z->left;
        RB_Transplant(D, z, z->left);
        freeNode(&z);
    }
    else{
        y = z->right;
        while (y->left != D->Dummy){
            y = y->left;
        }
        original_color = y->color;
        x = y->right;
        if (y->parent == z){
            x->parent = y;
        }
        else{
            RB_Transplant(D, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(D, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        freeNode(&z);
    }
    if (original_color == BLACK){
        RB_DeleteFixUp(D, x);
    }
    D->size--;
}

void freeInOrder(Dictionary D, Node x){
    if (x != D->Dummy){
        freeInOrder(D, x->left);
        freeInOrder(D, x->right);
        freeNode(&x);
    }
}

void makeEmpty(Dictionary D){
    if (D->size == 0){
        return;
    }
    //beginReverse(D);
//    while (D->size > 1){
////        delete(D, D->Cursor->key);
////        beginReverse(D);
//
//    }
    freeInOrder(D, D->Root);
    //delete(D, D->Root->key);
    D->Cursor = D->Root = D->Dummy;
    D->size = 0;
}

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

void InOrderTreeWalk(Dictionary D, Node x, FILE *out){
    if (x != D->Dummy){
        InOrderTreeWalk(D, x->left, out);
        fprintf( out ,"%s", x->key);
        InOrderTreeWalk(D, x->right, out);
    }
}

void PreOrderTreeWalk(Dictionary D, Node x, FILE *out){
    if (x != D->Dummy){
        fprintf(out, "%s", x->key);
        PreOrderTreeWalk(D, x->left, out);
        PreOrderTreeWalk(D, x->right, out);
    }
}

void PostOrderTreeWalk(Dictionary D, Node x, FILE *out){
    if (x != D->Dummy){
        PostOrderTreeWalk(D, x->left, out);
        PostOrderTreeWalk(D, x->right, out);
        fprintf(out, "%s", x->key);
    }
}

void printDictionary(FILE* out, Dictionary D, const char* ord){
    D->Cursor = D->Root;
    if (KEY_CMP(ord, "pre") == 0){
        fprintf(out, "******************************************************\n");
        fprintf(out, "PRE-ORDER:\n");
        fprintf(out, "******************************************************\n");
        PreOrderTreeWalk(D, D->Root, out);
    }
    else if (KEY_CMP(ord, "in") == 0){
        fprintf(out, "******************************************************\n");
        fprintf(out, "IN-ORDER:\n");
        fprintf(out, "******************************************************\n");
        InOrderTreeWalk(D, D->Root, out);
    }
    else if (KEY_CMP(ord, "post") == 0){
        fprintf(out, "******************************************************\n");
        fprintf(out, "POST-ORDER:\n");
        fprintf(out, "******************************************************\n");
        PostOrderTreeWalk(D, D->Root, out);
    }
    else{
        return;
    }
}
