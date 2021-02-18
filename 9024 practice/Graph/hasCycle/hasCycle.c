
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

int visited[1000];

bool dfsCycleCheck(Graph g, int prev, int curr){
	visited[curr] = 1;
	int n;
	for(n = 0; n < GraphNumVertices(g); n++){
		if (GraphIsAdjacent(g, curr, prev)){
			if (!visited[n]){
				if (dfsCycleCheck(g, curr, n)){
					return true;
				}
			} else if (n != prev){
				return true;
			}
		}
	}
	return false;
}



