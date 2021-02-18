// Priority Queue ADO implementation ... COMP9024 19T3

#include "PQueue.h"
#include <assert.h>
#include "stdio.h"

typedef struct {
    Vertex item[MAX_NODES];  // array of vertices currently in queue
    int length;           // #values currently stored in item[] array
} PQueueT;

static PQueueT PQueue;      // defines the Priority Queue Object


// set up empty priority queue
void PQueueInit() {
    PQueue.length = 0;
}

// insert vertex v into priority queue
// no effect if v is already in the queue
void joinPQueue(Vertex v) {
    assert(PQueue.length < MAX_NODES);                // ensure queue ADO is not full
    int i = 0;
    while (i < PQueue.length && PQueue.item[i] != v)  // check if v already in queue
        i++;
    if (i == PQueue.length) {                         // v not found => add it at the end
        PQueue.item[PQueue.length] = v;
        PQueue.length++;
    }
}

// remove the highest priority vertex from PQueue
// remember: highest priority = lowest value priority[v]
// returns the removed vertex
Vertex leavePQueue(int priority[]) {
    assert(PQueue.length > 0);                      // ensure queue ADO is not empty
    int min = 99999;
    int min_index = 0;
    int result = 0;
    for (int i = 0; i < PQueue.length; i++) {
        if (priority[PQueue.item[i]] < min) {
            min = priority[PQueue.item[i]];
            min_index = i;
            result = PQueue.item[i];
        }
    }
    PQueue.length--;
    for (int i = min_index; i < PQueue.length; i++) {
        PQueue.item[i] = PQueue.item[i + 1];
    }
    return result;
}

// check if priority queue PQueue is empty
bool PQueueIsEmpty() {
    if (PQueue.length != 0) return false;
    else return true;
}
