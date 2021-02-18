// PQueue client ... COMP9024 19T3
#include <stdio.h>
#include "PQueue.h"

int main(void) {
    int distance[] = {24, 90, 19};

    PQueueInit();

    joinPQueue(1);
    joinPQueue(2);
    joinPQueue(0);

    while (!PQueueIsEmpty()) {
        printf("Dequeueing %d.\n", leavePQueue(distance));
    }
    return 0;
}
