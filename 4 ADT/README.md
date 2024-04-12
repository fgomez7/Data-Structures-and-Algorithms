# Programming Assignment 4

By: Francisco Gomez

For this assignment, I pretty much made a similar implementation of
a doubly Linked list from the first programming assignment. 

____

__List.h:__
Header file for List ADT. List is a double ended queue with a vertical
cursor standing between elements. The cursor position is always defined
to be an int in the range 0 (at front) to length of List (at back).
An empty list consists of the vertical cursor only, with no elements.

__List.cpp:__
This is the brains of List.h which is almost beat by beat the
same as List.c from the 1st assignment. Holds two cursors that point at the
2 nodes which also includes 2 dummy nodes on the front of the list implementation
and the back. It also holds other operations such as moving the cursor throughout the list,
setting the cursor in the list either in the front or in the back, 
and/or giving the position of the cursor. 

__ListTest.cpp:__
A test client for List ADT which test the basic functions of List.h and List.cpp
which is pretty similar to the List.c from the first assignment

__Shuffle.cpp:__
Shuffle.cpp: the main file of this assignment which calculates the permutations
during perfect shuffles of any size deck

__Makefile:__
holds the set of directives which defines tasks that need to be
executed in order to compile my program

__README.md:__
A simple markdown file which gives a short summary of all the files
that I need to turn in and that are needed to turn in in order to
finish this programming assignment.