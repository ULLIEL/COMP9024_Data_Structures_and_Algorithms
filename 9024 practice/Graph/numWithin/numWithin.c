
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int numWithin(Graph g, int src, int dist) {
	if(dist == 0){
		return 1;
	}
	int visited[GraphNumVertices(g)];
	int distance[GraphNumVertices(g)];
	int v;
	Queue q = QueueNew();
	QueueEnqueue(q, src);
	int times;
		
	for (int i = 0; i < GraphNumVertices(g); i++){
		visited[i] = -1;
	}
	
	visited[src] = src;
	while(!QueueIsEmpty(q)){
		v = QueueDequeue(q);
		for (int i=0; i < GraphNumVertices(g); i++){
			if (visited[i] == -1 && GraphIsAdjacent(g, v, i)) {
				QueueEnqueue(q, i);
				visited[i] = v;
			}
		}
	}
		
	QueueFree(q);
	
	
	for (int i=0; i < GraphNumVertices(g); i++){
		v = visited[i];
		times = 0;
		while (v != src){
			if (v == -1){
				distance[i] = -1;
				break;
			}
			times++;
			v = visited[v];
		}
		distance[i] = times;
	}	
	
	times = 0;
	for (int i=0; i < GraphNumVertices(g); i++){
		if(distance[i] < dist && visited[i]>=0){
			times++;
		}		
	}
	
	return times;
}
