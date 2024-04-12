# Programming Assignment 5

By: Francisco Gomez

For this assignment, I was instructed to implement a binary
search tree which is helpful in many scenarios. Such as 
building a dictionary and sorting out lines of files no matter
how big they are. 

__Lex.c:__ For this file, this is the black box of the assignment. 
This file allows the user to input 2 files which can be read by the program. 
It will read every line and treat it as a string in which there
the binary tree would sort it out like a dictionary allowing the 
program to print out the file in Lexicographic order.

__DictionaryTest.c:__ this file is just another test file 
which test all of the functions that are held in Dictionary.h and 
Dictionary.c. To which it test weather they files work perfectly or not. 

__Dictionary.h:__ this file holds the structure of Dictionary.h.
It holds all of the required elements that need to be implemented in order
for the binary search tree to function properly. Helper functions are not included 
in this file.

__Dictionary.c:__ this file holds the implemented portion of Dictionary.h. 
It is basically the implementation of the binary search tree which helps
to sort every single key value. It holds functions which help traverse through 
the tree such as the cursor.

__Makefile:__
holds the set of directives which defines tasks that need to be
executed in order to compile my program

__README.md:__
A simple markdown file which gives a short summary of all the files
that I need to turn in and that are needed to turn in in order to
finish this programming assignment.

