
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void search(Graph g, int src, int *visited){
	visited[src] = 1;
	printf(" %d", src);
	
	for(int i = 0; i < GraphNumVertices(g); i++){
		if (!visited[i] && GraphIsAdjacent(g, src, i)){
			search(g, i, visited);
		}
	}
}


void depthFirstSearch(Graph g, int src) {
	int visited[GraphNumVertices(g)];
	
	for(int i = 0; i < GraphNumVertices(g); i++){
		visited[i] = 0;
	}
	search(g, src, visited);
}


