// DLList.c - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by John Shepherd, August 2014, August 2015
// Modified by Ashesh Mahidadia, December 2017 
// Modified by Hongpei Luo, January 2019 for the assiment of summer term

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "DLList.h"

struct DLListNode {
    char *value;                // value of this list item (string)
    struct DLListNode *next;    // pointer to next node in list
    DLList children;
};

struct ShowDLList {
    int nitems;           // count of items in list
    DLListNode first;     // first node in list
    DLListNode last;      // last node in list
};

// Create a new DLListNode
DLListNode newDLListNode(char *val) {
    DLListNode new = malloc(sizeof(struct DLListNode)); 
    assert(new != NULL);     
    new->value = malloc((strlen(val) + 1) * sizeof(char));
    assert(new->value != NULL);
    strcpy(new->value, val);
    new->value[strlen(val)] = '\0';
    new->next = NULL;
    new->children = NULL;
    return new;
}

// Create an empty DLList
DLList newDLList() {
    DLList L = malloc(sizeof(struct ShowDLList));
    assert(L != NULL);
    L->nitems = 0;
    L->first = NULL;
    L->last = NULL;
    return L;
}

// Mainly to check if the word is repetitive and delete the repetitive one
DLListNode existDLList(DLList L, char *val) {
    assert(L != NULL);
    DLListNode curr = L->first;
    while (curr != NULL) {
        // check if the strings are the same
        if (strcmp(curr->value, val) == 0) {
            break;
        }
        curr = curr->next;
    }
    return curr;
}

void addDLList(DLList L, char *val) {
    assert(L != NULL);
    DLListNode existNode = existDLList(L, val);
    if (existNode == NULL) {
        // get the new node
        DLListNode newNode = newDLListNode(val);

        if (L->last == NULL) {
            L->first = L->last = newNode;
            L->nitems++;
        } else {
            L->last->next = newNode;
            L->last = L->last->next;
            L->nitems++;
        }
    }
}


void addDLListAndChild(DLList L, char *val, char *child) {
    assert(L != NULL);
    DLListNode existNode = existDLList(L, val);
    if (existNode == NULL) {
        addDLList(L, val);
        existNode = L->last;
    }
    if (existNode->children == NULL) {
        existNode->children = newDLList();
    }

    addDLList(existNode->children, child);
}

// Display the word and url, with comma separated, use this function to printf to check if the output is right
void showDLList(DLList L) {
    assert(L != NULL);
    DLListNode curr, child;
    for (curr = L->first; curr != NULL; curr = curr->next) {
        fprintf(stdout, "%s", curr->value);
        if (curr->children != NULL) {
            for (child = curr->children->first; child != NULL; child = child->next) {
                fprintf(stdout, " %s", child->value);
            }
        }
        fprintf(stdout, "\n");
    }

}

// covert DLList to Array
void convertDLListToArray(DLList L, char **array) {
    assert(L != NULL);
    int index = 0;
    DLListNode curr;
    for (curr = L->first; curr != NULL; curr = curr->next) {
        // copy value
        array[index] = malloc(sizeof(strlen(curr->value) + 1));
        strcpy(array[index], curr->value);
        array[index][strlen(curr->value) + 1] = '\0';
        index++;
    }
}

DLListNode insertSortNode(DLListNode head) {
    DLListNode first,t,p,q;
    first = head->next;
    head->next = NULL;
    while (first != NULL) {
        for (t = first, q = head; ((q != NULL) && (strcmp(q->value, t->value) < 0)); p = q, q = q->next);
        first = first->next;
        if (q == head) {
            head = t;
        } else {
            p->next = t;
        }
        t->next = q;
    }

    return head;
}


void sortDLList(DLList L) {
    // sort insertion
    L->first = insertSortNode(L->first);
}

// Write the data to invertedIndex.txt
void writeinvertedIndex(DLList L) {
    assert(L != NULL);
    FILE *file;

    if ((file = fopen("invertedIndex.txt", "w")) != NULL) {
        DLListNode curr, child;
        for (curr = L->first; curr != NULL; curr = curr->next) {
            fprintf(file, "%s", curr->value);
            if (curr->children != NULL) {
                for (child = curr->children->first; child != NULL; child = child->next) {
                    fprintf(file, " %s", child->value);
                }
            }
            fprintf(file, "\n");
        }

        fclose(file);
    }
}

// Free the space
void freeDLList(DLList L) {
    assert(L != NULL);
    DLListNode curr, prev;
    curr = L->first;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;

        // free value and current node
        if (prev->children != NULL) {
            freeDLList(prev->children);
        }
        free((prev->value));
        free(prev);
    }
    free(L);
}