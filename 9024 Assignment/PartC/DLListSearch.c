/*
 Implementation of doubly-linked list ADT for string values.
 Written by Ashesh Mahidadia Jan 2018, based on code writted by John Shepherd 2015.
 You may need to modify the following implementation and test it properly before using 
 in your program.

 Modified by Hongpei Luo Jan, 2020 for assignment in summer term
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "DLListSearch.h"

struct DLListNode {
    char *value;  // value of this list item (string)
    // pointer previous node in list
    struct DLListNode *next;
    // pointer to next node in list
    int numberOfDegrees;
    int count;
    double rankValue;
    DLList children;
} ;

// data structures representing DLList
struct DLListRep {
    DLListNode first; // first node in list
    DLListNode last;  // last node in list
    int nitems;      // count of items in list
} ;


// Create a new DLListNode
DLListNode newDLListNode(char *val, int numberOfDegrees, double rankValue) {
    DLListNode new = malloc(sizeof(struct DLListNode));
    assert(new != NULL);
    new->value = malloc((strlen(val) + 1) * sizeof(char));
    assert(new->value != NULL);
    strcpy(new->value, val);
    new->value[strlen(val)] = '\0';
    new->numberOfDegrees = numberOfDegrees;
    new->rankValue = rankValue;
    new->count = 0;
    new->next = NULL;
    new->children = NULL;
    return new;
}

// Create a new DLList
DLList newDLList() {
    DLList L = malloc(sizeof(struct DLListRep));
    assert(L != NULL);
    L->nitems = 0;
    L->first = NULL;
    L->last = NULL;
    return L;
}

DLListNode existDLList(DLList L, char *val) {
    assert(L != NULL);

    DLListNode curr = L->first;
    while (curr != NULL) {
        if (strcmp(curr->value, val) == 0) {
            break;
        }
        curr = curr->next;
    }
    return curr;
}

DLListNode addDLList(DLList L, char *val, int numberOfDegree, double rankValue) {
    assert(L != NULL);

    if (L->first == NULL) {
        L->first = L->last = newDLListNode(val, numberOfDegree, rankValue);
        L->nitems++;
        return L->first;
    } else {
        if (strcmp(L->first->value, val) == 0) {
            return L->first;
        }
        else if (strcmp(L->first->value, val) > 0) {
            DLListNode newNode = newDLListNode(val, numberOfDegree, rankValue);
            newNode->next = L->first;
            L->first = newNode;
            L->nitems++;

            return L->first;
        } else {
            DLListNode first = L->first, second = L->first->next;
            while (second != NULL) {
                if (strcmp(second->value, val) == 0) {
                    return second;
                }

                if (strcmp(second->value, val) > 0) {
                    break;
                }

                second = second->next;
                first = first->next;
            }
            DLListNode newNode = newDLListNode(val, numberOfDegree, rankValue);
            if (second == NULL) {
                L->last->next = newNode;
                L->last = L->last->next;
                L->nitems++;
            } else {
                first->next = newNode;
                newNode->next = second;
                L->nitems++;
            }

            return newNode;
        }
    }
}

void addDLListAndChild(DLList L, char *val, char *child) {
    assert(L != NULL);
    DLListNode existNode = addDLList(L, val,0,0.0);

    if (existNode->children == NULL) {
        existNode->children = newDLList();
    }

    // addnode
    addDLList(existNode->children, child,0,0.0);
}


// Display
void showDLList(DLList L) {
    assert(L != NULL);
    DLListNode curr, child;
    for (curr = L->first; curr != NULL; curr = curr->next) {
        fprintf(stdout, "%s--%lf", curr->value, curr->rankValue);
        if (curr->children != NULL) {
            for (child = curr->children->first; child != NULL; child = child->next) {
                fprintf(stdout, "%s--%lf", child->value, child->rankValue);
            }
        }
        fprintf(stdout, "\n");
    }
}


// Free up all space associated with list
void freeDLList(DLList L) {
    assert(L != NULL);
    DLListNode curr, prev;
    curr = L->first;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;

        if (prev->children != NULL) {
            freeDLList(prev->children);
        }
        free((prev->value));
        free(prev);
    }
    free(L);
}

int lengthDLList(DLList L) {

    assert(L != NULL);
    return L->nitems;
}

DLListNode insertSortNode(DLListNode head) {
    DLListNode first, t, p, q;
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

void searchInvertedDLList(DLList paramsList, DLList pageRankList, DLList invertedIndexList, DLList searchResultList) {
    assert(paramsList != NULL);
    assert(pageRankList != NULL);
    assert(invertedIndexList != NULL);
    assert(searchResultList != NULL);

    DLListNode paramFirst = paramsList->first, invertedIndexFirst, existNode;

    while (paramFirst != NULL) {
        invertedIndexFirst = invertedIndexList->first;
        while (invertedIndexFirst != NULL) {
            // compare
            if (strcmp(paramFirst->value, invertedIndexFirst->value) == 0) {
                if (invertedIndexFirst->children != NULL) {
                    DLListNode urlNode = invertedIndexFirst->children->first;
                    DLListNode rankNode;
                    while (urlNode != NULL) {
                        rankNode = pageRankList->first;
                        while (rankNode != NULL) {
                            if (strcmp(urlNode->value, rankNode->value) == 0) {
                                rankNode->rankValue++;
                            }
                            rankNode = rankNode->next;
                        }
                        urlNode = urlNode->next;
                    }

                }
            }
            invertedIndexFirst = invertedIndexFirst->next;
        }
        paramFirst = paramFirst->next;
    }

}

void copyPagerank(DLList pageRankList,float *pagerank){
    DLListNode curr = pageRankList->first;
    
    for (int i = lengthDLList(pageRankList)-1; i>=0; i--){
        pagerank[i] = curr->rankValue;
        curr = curr->next;
    }
    
}

void printUrl(DLList pageRankList, int *printNum){
    int num = lengthDLList(pageRankList), j;
    DLListNode curr;
    for(int i=num-1; i>0; i--){
        j = printNum[i]-1;
        curr = pageRankList->first;
        for (; j>0; j--){
            curr = curr->next;
        }
        if (curr->rankValue >1){
            printf("%s\n", curr->value);
        }
    }
}
