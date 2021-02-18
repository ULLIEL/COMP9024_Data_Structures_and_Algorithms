#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int shortestDistance(Graph g, int src, int dest) {
	int visited[GraphNumVertices(g)];
	int current;
	Queue queue = QueueNew();
	QueueEnqueue(queue, src);
	
	for (int i = 0; i < GraphNumVertices(g); i++){
		visited[i] = -1;
	}
	visited[src] = src;
	while(!QueueIsEmpty(queue)){
		current = QueueDequeue(queue);
		for (int i = 0; i < GraphNumVertices(g); i++){
			if (visited[i] == -1 && GraphIsAdjacent(g, current, i)){
				QueueEnqueue(queue, i);
				visited[i] = current;
			}
		}
	}
	
	QueueFree(queue);
	
	int distance = 0;
	while (dest != src) {
		if (dest == -1){
			return -1;
		}
		dest = visited[dest];
		distance++;
	}
	return distance;
}

