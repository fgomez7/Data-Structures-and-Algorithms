// Francisco Gomez         Cruz id: 1775128        Feb 7, 2021
// This is the brains of List.h which is almost beat by beat the 
// same as List.c from the 1st assignment. Holds two cursors that point at the 
// 2 nodes which also includes 2 dummy nodes on the front of the list implementation 
// and the back. It also holds other operations such as moving the cursor throughout the list
#include<string>
#include<iostream>
#include "List.h"

using namespace std;

//node constructor

List::Node::Node(int x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List() {
    Node *N = new Node(-1);
    frontDummy = N;
    Node *M = new Node(-1);
    backDummy = M;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    //front_1 = nullptr;
    //front_2 = nullptr;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List &L) {//copies the constructor
    Node *N = new Node(-1);
    frontDummy = N;
    Node *M = new Node(-1);
    backDummy = M;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    //front_1 = nullptr;
    //front_2 = nullptr;
    pos_cursor = 0;
    num_elements = 0;

    //load elements of L onto "this"
    Node* list = L.frontDummy;
    list = list->next;
    while (list->data != -1){
        insertBefore(list->data);
        list = list->next;
    }
}

List::~List() {
    clear();
    beforeCursor = nullptr;
    afterCursor = nullptr;
    //front_1 = nullptr;
    //front_2 = nullptr;
//    delete beforeCursor;
//    delete afterCursor;
    delete frontDummy;
    delete backDummy;
    frontDummy = nullptr;
    backDummy = nullptr;

}

bool List::isEmpty() {
    if (num_elements == 0){
        return true;
    } else{
        return false;
    }
}

int List::size(){
    return num_elements;
}

int List::position() {
    return pos_cursor;
}

void List::moveFront() {
    if (isEmpty()){
        cerr << "Stack Error: calling moveFront() on an empty List" << endl;
        exit(EXIT_FAILURE);
    }
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack() {
    if (isEmpty()){
        cerr << "Stack Error: calling moveBack() on an empty List" << endl;
        exit(EXIT_FAILURE);
    }
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

int List::peekNext() {
    if (position() < size()){
        return afterCursor->data;
    }
    return -1;
}

int List::peekPrev() {
    if (position() > 0){
        return beforeCursor->data;
    }
    return -1;
}

int List::moveNext() {
    if (position() < size()){
        beforeCursor = beforeCursor->next;
        afterCursor = afterCursor->next;
        pos_cursor++;
        return beforeCursor->data;

    }
    exit(EXIT_FAILURE);
}

int List::movePrev() {
    if (position() > 0){
        beforeCursor = beforeCursor->prev;
        afterCursor = afterCursor->prev;
        pos_cursor--;
        return afterCursor->data;
    }
    exit(EXIT_FAILURE);
}

void List::insertAfter(int x) {
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
}

void List::insertBefore(int x) {
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    pos_cursor++;
    num_elements++;
}

void List::eraseAfter() {
    if (position() < size()){
        Node *N = afterCursor;
        afterCursor = N->next;
        afterCursor->prev = beforeCursor;
        beforeCursor->next = afterCursor;
        num_elements--;
        delete N;
    }
}

void List::eraseBefore() {
    if (position() > 0){
        Node *N = beforeCursor;
        beforeCursor = N->prev;
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
        num_elements--;
        pos_cursor--;
        delete N;
    }
}

int List::findNext(int x) {
    while (pos_cursor < num_elements){
        if (peekNext() == x){
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    //moveNext();
    return -1;
}

int List::findPrev(int x) {
    while (pos_cursor > 0){
        if (peekPrev() == x){
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    return -1;
}

void List::cleanup() {
    Node* front_1 = frontDummy->next;
    Node* front_2 = front_1;

    int position = 2, counter = 1;
    int data_1 = front_1->data;
    int data_2 = front_2->data;

    for (front_2 = front_2->next; front_1->data != -1 ; front_1 = front_1->next) {
        data_1 = front_1->data;
        data_2 = front_2->data;
        while (front_2->data != -1){
            if (data_1 == data_2){
                counter ++;
                if (counter == 1){
                    front_2 = front_2->next;
                    data_2 = front_2->data;
                    position ++;
                    continue;
                }
                if (position == pos_cursor + 1){
                    front_2 = front_2->next;
                    data_2 = front_2->data;
                    eraseAfter();
                    continue;
                }
                if (position == pos_cursor){
                    front_2 = front_2->next;
                    data_2 = front_2->data;
                    eraseBefore();
                    continue;
                }
                if (position < pos_cursor){
                    //position--;
                    pos_cursor --;
                }
                Node *Hakai = front_2;
                front_2 = Hakai->next;
                front_2->prev = Hakai->prev;
                Hakai->prev->next = front_2;
                data_2 = front_2->data;
                delete Hakai;
                num_elements --;
                continue;
            }
            front_2 = front_2->next;
            data_2 = front_2->data;
            position ++;
        }
        front_2 = frontDummy->next;
        data_2 = front_2->data;
        position = 1;
        counter = 0;
    }
}

void List::clear() {
    if (num_elements != 0){
        moveFront();
        while (num_elements > 0){
            eraseAfter();
        }
    }

}

List List::concat(const List &L) {
    List New;
    moveFront();
    //New.moveFront();
    for (peekNext(); peekNext() != -1 ; moveNext()) {
        New.insertBefore(peekNext());
    }
    New.moveBack();
    Node *node = L.frontDummy;
    for (node = node->next; node->data != -1 ; node = node->next) {
        New.insertBefore(node->data);
    }
    New.moveFront();
    return New;
}

string List::to_string() {
    Node *N = frontDummy;
    string s = "";
    for (N = N->next; N->data != -1; N = N->next) {
        s += std::to_string(N->data)+" ";
    }
    return s;
}

bool List::equals(const List &R) {
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (this->size() == R.num_elements);
    N = frontDummy->next;
    M = R.frontDummy->next;
    while (eq && N!= nullptr){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }

    return eq;
}

ostream& operator<< ( ostream& stream, List& L ){
    return stream << L.List::to_string();
}

bool operator==(List& A, const List& B){
    return A.List::equals(B);
}

List& List::operator=(const List &L) {
    if (this != &L){
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        //std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}
