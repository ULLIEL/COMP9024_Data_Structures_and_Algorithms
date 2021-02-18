// Starting code for Dijkstra's algorithm ... COMP9024 19T3

#include <stdio.h>
#include <stdbool.h>
#include "PQueue.h"

#define VERY_HIGH_VALUE 999999

void dijkstraSSSP(Graph g, Vertex source) {
    int dist[MAX_NODES];
    int pred[MAX_NODES];
    bool vSet[MAX_NODES];  // vSet[v] = true <=> v has not been processed
    int s;
    int k = 0;

    PQueueInit();
    int nV = numOfVertices(g);
    for (s = 0; s < nV; s++) {
        joinPQueue(s);
        dist[s] = VERY_HIGH_VALUE;
        pred[s] = -1;
        vSet[s] = true;
    }
    dist[source] = 0;

    /* NEEDS TO BE COMPLETED */
    vSet[source] = false;

    for (int i = 0; i < nV; i++) {

        k = leavePQueue(dist);
        vSet[k] = false;

        for (int j = 0; j < nV; j++) {
            int tmp = adjacent(g, k, j);
            if (tmp == 0) {
                tmp = VERY_HIGH_VALUE;
            } else {
                tmp += dist[k];
            }
            if (vSet[j] == true && (tmp < dist[j])) {
                dist[j] = tmp;
                pred[j] = k;
            }
        }
    }

    for (int i = 0; i < nV; i++) {
        if (dist[i] < VERY_HIGH_VALUE) {
            printf("%d: distance = %d, shortest path: ", i, dist[i]);
            int aaa[1000];
            int cont = 0;
            aaa[0] = i;
            int v = i;
            while (pred[v] != -1) {
                cont++;
                aaa[cont] = pred[v];
                v = pred[v];
            }
            for (int h = cont; h > 0; h--) {
                printf("%d-", aaa[h]);
            }
            printf("%d\n", aaa[0]);
        } else {
            printf("%d: no path\n", i);
        }
    }

}


void reverseEdge(Edge *e) {
    Vertex temp = e->v;
    e->v = e->w;
    e->w = temp;
}

int main(void) {
    Edge e;
    int n, source;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph g = newGraph(n);

    printf("Enter the source node: ");
    scanf("%d", &source);
    printf("Enter an edge (from): ");
    while (scanf("%d", &e.v) == 1) {
        printf("Enter an edge (to): ");
        scanf("%d", &e.w);
        printf("Enter the weight: ");
        scanf("%d", &e.weight);
        insertEdge(g, e);
        reverseEdge(&e);               // ensure to add edge in both directions
        insertEdge(g, e);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");

    dijkstraSSSP(g, source);
    freeGraph(g);
    return 0;
}
