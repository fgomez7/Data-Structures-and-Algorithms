# Programming Assignment 1

by: Francisco Gomez cruz id: 1775128 1/16/2021

__List.h__ :

 Is a header file holding all of the functions needed for List.c. Most of the functions I obtained from the Pa1 pdf in the cse101. Other functions I got from queue.c.

 __List.c__ :

 Is a c file which is linked to List.h. List.c holds all the functions that ListClient.c uses as well as Lex.c. List.c holds all the functions which allows the program to make a doubly linked list where within each node in the list contains a data (x). Each function has a different purpose from appending nodes into the list to deleting the entire list itself. To traverse through the list, a cursor was also implemented which points to a specific node in the doubly linked list. 

 __ListClient.c__:

This is a main() c file which test the functions in List.c file that I have written. It tests out the basics and almost nothing has been changed in this file. 

__Lex.c__:

Is another .c file that was written by me. The purpose of this main file is to sort strings from a file and write the sorted strings to an out file using List.c and insertion sort. Some of the functions used in the main file were brought from FILEIO.c in the examples folder in cse101 websites. 

__Makefile__:

Another file that is used to compile all of the header files, the .c files as well as the other main.c files that generates a target. It was given to me.

__README__:

Is a markdown file which is a table of contents that describe everything that I'm turning in for this programming assignment. 

