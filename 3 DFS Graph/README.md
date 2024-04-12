# Programming Assignment 3
by Francisco Gomez

For this programming assignment, i've been instructed to implement the search function known as DFS which is somewhat different from the other function i've implemented BFS. 
Although, this search function does not use nor does it need a source to search through a graph unlike BFS

__List.h__ :

Is a header file holding all of the functions needed 
for List.c. Most of the functions I obtained from the Pa1 pdf in the cse101. Other functions I got from queue.c.

__List.c__ :

Is a c file which is linked to List.h. List.c holds all the functions that ListClient.c uses as well
as Lex.c. List.c holds all the functions which allows the program to make a doubly linked list where within each node
in the list contains a data (x). Each function has a different purpose from appending nodes into the list to deleting the entire list itself.
To traverse through the list, a cursor was also implemented which points to a specific node in the doubly linked list. 

__Graph.h__:

In Graph.h, it holds the structure to Graph.c with all of its function needed to implement a graph in C code
. From connected to disconnected graphs.

__Graph.c__:

In Graph.c, holds all of the functions that are necessary in order to implement 
the DFS search algorithm. Just like BFS, it is used to make a graph and traverse through all of the vertices but in comparison with  DFS, 
it doesn't need a source number in order to traverse through all of the vertices of the graph.

__GraphClient.c__:

This is just a simple file which I derived from the original graphclient.c file which was 
given to us under the examples folder in the CSE101 folder. This file basically tests out the functionality of 
all of the functions that i've implemented in Graph.c. 

__FindComponents.c__:

Find components is used to test out the functionality of the DFS implementation i've made in Graph.c. 
It pretty much traverses through all of the vertices in a graph even if they are bidirectional or not without the use of a source number. 
Just like GraphClient.c but this makes sure no matter what graph is thrown at this file, it will make sure 
to give out all of the information accurately such as the discovered and finished times of all the vertices as well as the Trasnpose 
version of the graphs as well. 


This is all I have to say, thank you for your time. 