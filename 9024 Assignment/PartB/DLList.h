// DLList.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, Ashesh Mahidadia, Jan 2017 
// Modified by Hongpei Luo, January 2019 for the assiment of summer term

#ifndef DLList_H
#define DLList_H

#include <stdio.h>
#include <stdbool.h>

// External view of DLList
// Implementation given in DLList.c
// Implements a DLList of string
typedef struct DLListNode *DLListNode;

typedef struct ShowDLList *DLList;

// Create a new empty DLList
DLList newDLList();

// Insert value set
void addDLList(DLList, char *);

// Insert value and child
void addDLListAndChild(DLList, char *, char *);

// Display items from a DLList, comma separated
void showDLList(DLList);

// Write the data to invertedIndex.txt
void writeinvertedIndex(DLList L);

// Free the space
void freeDLList(DLList L);

// Covert DLList to Array
void sortDLList(DLList);
void convertDLListToArray(DLList, char **);

#endif
