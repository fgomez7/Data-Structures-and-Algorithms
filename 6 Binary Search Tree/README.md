# Programming Assignment 6

By: Francisco Gomez

For this assignment, I had to implement a red black tree. It is quite similar to a binary search tree
but holds different properties. It holds more properties. For every node, it has a color which determines
the properties of the tree with colors RED and BLACK. It organizes the tree which in return implements
a more well sorted and balanced search tree than a binary search tree of it self. It pertains numerous 
helper functions which were kindly provided in the pseudo code that the professor has given us. 

__Dictionary.h:__ this file holds the structure of Dictionary.h. It holds all of the required elements that
need to be implemented in order for the RED BLACK TREE to function properly. Helper functions are not 
included in this file.

__Dictionary.c:__ this file holds the implemented portion of Dictionary.h. It is basically the 
implementation of the red black tree which helps to sort every single key value. It holds functions which
help traverse though the tree with the help of an implemented cursor.

__DictionaryTest.c__ This file is just another test file which test all of the functions that are held in Dictionary.h
and Dictionary.c. To which it test whether the files work perfectly or not.

__Order.c__ This file is the black box of the assignment. It takes in 2 files where on one file, it will
read all of its lines and sort the strings in a red black tree. And the other file is an output file which
shoes the lines of the original file printed in Lexicographic order as well as it is printed in 3 ways
depending on the outcome of the tree which is in a preorder, inorder, and postorder tree walk.

__Makefile:__
holds the set of directives which defines tasks that need to be
executed in order to compile my program

__README.md:__
A simple markdown file which gives a short summary of all the files
that I need to turn in and that are needed to turn in in order to
finish this programming assignment.

