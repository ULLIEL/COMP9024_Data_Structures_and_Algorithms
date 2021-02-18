// DLList.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, Ashesh Mahidadia, Jan 2017 
// Modified by Hongpei Luo, Jan 2020

#ifndef DLList_H
#define DLList_H

#include <stdio.h>
#include <stdbool.h>

typedef struct DLListNode *DLListNode;

typedef struct DLListRep *DLList;

// Create a new empty DLList
DLList newDLList();

DLListNode addDLList(DLList , char *, int, double);

// Add value and child
void addDLListAndChild(DLList, char *, char *);

// Free space
void freeDLList(DLList);

// Show word and url
void showDLList(DLList);

// The length of DLList
int lengthDLList(DLList);

// Search inverted DLList
void searchInvertedDLList(DLList, DLList, DLList,DLList);

// Copy the pagerank
void copyPagerank(DLList pageRankList,float *pagerank);

// Print the standard output
void printUrl(DLList pageRankList, int *printNum);

#endif
