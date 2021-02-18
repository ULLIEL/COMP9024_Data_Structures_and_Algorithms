
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int num;

void search(Graph g, int src, int *visited){
	visited[src] = 1;
	for (int i = 0; i < GraphNumVertices(g); i++){
		if (!visited[i] && GraphIsAdjacent(g, src, i)){
			search(g, i, visited);
			num++;
		}
	}
}

int numReachable(Graph g, int src) {
	num = 1;
	int visited[GraphNumVertices(g)];
	
	for (int i = 0; i < GraphNumVertices(g); i++){
		visited[i] = 0;
	}
	
	search(g, src, visited);
	return num;
	
}

