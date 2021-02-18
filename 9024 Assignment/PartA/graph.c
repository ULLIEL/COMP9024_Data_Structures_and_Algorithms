// Graph ADT
// Modified from Adjacency Matrix Representation ... COMP9024 19T3
/* 
	Modified by Hongpei Luo (mainly modify it from undirected graph to directed graph, and compute the number of out-degree of url)
*/

#include "graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct GraphRep {
	int  **edges;   // adjacency matrix
	int    nV;      // #vertices
	int    nE;      // #edges
} GraphRep;

Graph newGraph(int V) {
	assert(V >= 0);
	int i;

	Graph g = malloc(sizeof(GraphRep));
	assert(g != NULL);
	g->nV = V;
	g->nE = 0;

	// allocate memory for each row
	g->edges = malloc(V * sizeof(int *));
	assert(g->edges != NULL);
	// allocate memory for each column and initialise with 0
	for (i = 0; i < V; i++) {
		g->edges[i] = calloc(V, sizeof(int));
		assert(g->edges[i] != NULL);
	}

	return g;
}

int numOfVertices(Graph g) {
	return g->nV;
}

// check if vertex is valid in a graph
bool validV(Graph g, Vertex v) {
//	return (g != NULL && v >= 0 && v < g->nV);
	return true;
}

void insertEdge(Graph g, Edge e) {
	assert(g != NULL && validV(g,e.v) && validV(g,e.w));

	if (!g->edges[e.v][e.w]) {  // edge e not in graph
		g->edges[e.v][e.w] = 1;
//		g->edges[e.w][e.v] = 1;
		g->nE++;
	}
}

void removeEdge(Graph g, Edge e) {
	assert(g != NULL && validV(g,e.v) && validV(g,e.w));

	if (g->edges[e.v][e.w]) {   // edge e in graph
		g->edges[e.v][e.w] = 0;
//		g->edges[e.w][e.v] = 0;
		g->nE--;
	}
}

bool adjacent(Graph g, Vertex v, Vertex w) {
	assert(g != NULL && validV(g,v) && validV(g,w));

	return (g->edges[v][w] != 0);
}

void freeGraph(Graph g) {
	assert(g != NULL);
	int i;
	for (i = 0; i < g->nV; i++)
		free(g->edges[i]);
	free(g->edges);
	free(g);
}

// To get the number of out-degree
int getNumberOfOutDegrees(Graph g, Vertex v) {
	assert(g != NULL);
	int num = 0;
	for (int i = 0; i < g->nV; i++) {
		if (adjacent(g, v, i)) {
			num++;
		}
	}
	return num;
}

