# Programming Assignment 2

by Francisco Gomez, Cruz id: 1774128

__List.h__ :

 Is a header file holding all of the functions needed for List.c. Most of the functions I obtained from the Pa1 pdf in the cse101. Other functions I got from queue.c.

 __List.c__ :

 Is a c file which is linked to List.h. List.c holds all the functions that ListClient.c uses as well as Lex.c. List.c holds all the functions which allows the program to make a doubly linked list where within each node in the list contains a data (x). Each function has a different purpose from appending nodes into the list to deleting the entire list itself. To traverse through the list, a cursor was also implemented which points to a specific node in the doubly linked list. 

 __Graph.h__:
 
 In Graph.h, it holds the structure to Graph.c with all of its function needed to implement a graph in C code. From connected to disconnected graphs. 

 __Graph.c__:

 In here, it holds all of the graph objects needed to make, build, modify and delete a graph. The majority of the functions I made were from the pa2 pdf such as getSource. Although, I did make functions of my own that made my life easier. For instance, I made set_source which changes the source of the graph. I only used it to print the adj list of the graph. I also made aonother function called sort_adj which I used to sort the adjacency of the graph from the smallest number to the greatest on order to prevent any further trouble when calling the bfs function and using get path and print path. 

 __GraphTest.c__:

 Its the last file which I derived from the original GraphTest.c in the example handout. I used it to test it's basic functionality such as printing a path, making a path, running bfs, making a null graph, and just making sure all of the get() functions would be returning the correct int. Mainly because I couldn't think of any edge cases or other preconditions to add to Graph.c. As long as it passed a simple graph, then I only deemed it worthy to be tested by the grading scripts. 

 __FindPath.c__:

 Is the main file of this assingment and it is used to pretty much test my header and c files to the professors grading scripts. I didn't really do anything to special. I took some of the elements from Lex.c in order to make FindPath.c. I ran 2 different while loops that would append the edges in the first half of the while loop and the other would find the path for the remaining secondary portion of the file after the dummy (0 0) that were present in the infile.txt.

 thank you for your time