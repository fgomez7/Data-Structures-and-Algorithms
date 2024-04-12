#Programming Assignment 7

by: Francisco Gomez

For this assignment, BigInteger.c needed to be implemented in order to calculate
the outcome of big integers/numbers that  cannot be calculated with the standard
arithmetic operations from c or other programming languages for that matter. So low level
languages require string implementation as well as normalization and other functions
in order to calculate the outcome of big numbers through arithmetic procedures that include and are limited to Addition,
Subtraction, and Multiplication. 

__List.h:__ this file is a remnant from the original List.h from the first 
assignment. Although it went though many changed in order to accommodate the 
new file needed in order for this assignment to work well. It includes many helper functions
which are used by BigInteger.c and the equals function was turned to equals_list since
was able to find some use for it. And also, its int was turned to long characters to accommodate
the bigger numbers that are being used. 

__List.c:__ this file holds the implementations from List.h. There really isn't much to say about this file
other than that it went though almost the same changes as List.h. Although this file
does hold the implementations of List.h which is the only major big difference between the both
of them. It holds the implementation of a doubly linked list which  holds the values in order
to calculate the arithmetic procedures that bigger numbers go through in order to calculate the outcome.

__ListTest.c:__ holds a simple .c file which tests all of the functions that are in List.c. Testing the 
overall changes that I made to the List.c and List.h files themselves as well as the functions that 
they contain in order to see the similarities and differences. All of this is done in order 
to make sure that List.c and List.h functions properly with BigInteger.c and BigInteger.h.

__BigInteger.h:__ holds the structural form of BigInteger.c as well as the functions that are
needed to calculate the outcome of bigger numbers going through an arithmetic process that
normal low level languages can't handle with the standard arithmetic functions. 

__BigInteger.c:__ holds the implementation of BigInteger.h in which it also uses the functions in List.h
to calculate the result of huge numbers when undergone through either addition, subtraction, or multiplication.
It uses many helper functions located in List.h and works fairly well. For the final test, it takes roughly 20 seconds
for the function to spit out the final and correct result. It may not be efficient but it gets the job done.

__BigIntegerTest.c:__ is just a simple file which tests the overall functionality of my implementation of BigInteger.c.
Through this file, I was able to test all the functions. Even though some of those functions may not appear
ont he .c file themselves, they are called by other functions which depending on the outcome, tells me which function is at fault
for me to correct. 

__Arithmetic.c:__ is the main focus of this assignment, the black box if you will.
Through this file, it test the overall functionality of BigInteger.c and .h as well as List.c 
and List.h. It works to accommodate the basic arithmetic operations (addition, subtraction, multiplication)
with 10 different really big numbers that aren't able to be calculated through the basic standard functions in lower level languages.
It works fine, although the final test case 5, takes roughly 20 seconds to completely spit out the final
and correct result but at least it works and when tested in the timeshare, it passes as well.

__Makefile:__
holds the set of directives which defines tasks that need to be
executed in order to compile my program.

__README.md:__
A simple markdown file which gives a short summary of all the files
that I need to turn in and that are needed to turn in in order to
finish this programming assignment.
