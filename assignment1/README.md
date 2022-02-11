# Assignment 1: Bubble Sort on a doubly linked list

## Description
This program will review concepts from CS202 including templates, classes, structs, file IO,
linked list, operator overloading, and pointers.

The program will read through a file and read each item into a node inside a linked list. 
The nodes will be sorted from least to greatest using bubble sort. However, the nodes
will not be swapped just by value, but swapping the whole node of the linked list.

This doubly linked list is not sorted by any counter loops but with an iterator object
that I created.

Since we are using templates, this program can sort strings, ints, floats, etc.

## Sample Run
```
Enter file with list: small.txt
Original List
10 5 9 3 7 12 2 4 11 1

Sorted List
1 2 3 4 5 7 9 10 11 12
```
