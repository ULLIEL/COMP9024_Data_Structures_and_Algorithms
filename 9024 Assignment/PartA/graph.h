// Graph ADT interface ... COMP9024 19T3
#include <stdbool.h>

typedef struct GraphRep *Graph;

// Make vertices in integers
typedef int Vertex;

// One edge is structed by two points
typedef struct Edge {
	Vertex v;
	Vertex w;
} Edge;

// Create the new graph
Graph newGraph(int);

// Get the number of vertices which is the same as the number of url
int   numOfVertices(Graph);

// Get the number of out-degrees of urls
int getNumberOfOutDegrees(Graph g, Vertex v);

// Insert edges
void  insertEdge(Graph, Edge);

// Remove edges
void  removeEdge(Graph, Edge);

// Free the graph
void  freeGraph(Graph);

// Check if is adjacent
bool  adjacent(Graph, Vertex, Vertex);