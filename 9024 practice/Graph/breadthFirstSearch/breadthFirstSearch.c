
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
	int numberOfVertex = GraphNumVertices(g);
	int *visited = malloc(sizeof(int) * numberOfVertex);
	
	for (int i = 0; i < numberOfVertex; i++){
		visited[i] = 0;
	}

	Queue queue = QueueNew();
	
	QueueEnqueue(queue, src);
	
	while (!QueueIsEmpty(queue)){
		int current = QueueDequeue(queue);
		
		if (visited[current] == 0){
			printf(" %d", current);
			visited[current] = 1;
			for (int i = 0; i < numberOfVertex; i++){
				if (!visited[i] && GraphIsAdjacent(g, current, i)){
					QueueEnqueue(queue, i);
				}
			}
		}
	}
	
	free(visited);
	QueueFree(queue);
	
}



