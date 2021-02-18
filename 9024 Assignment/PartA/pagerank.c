#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graph.h"
#define FAIL "Fail to read!"
#define MAX_LINE 1000

// Read collection.txt, also calculate the number of url
int ReadCollection(){
	char buf[MAX_LINE];  //buffer//
	FILE *fp;            //point to file//
	int N = 0;	         // number of url//
		
	if ((fp = fopen("collection.txt","r")) == NULL){
		perror("fail to read");
		exit (1);
	} else {
		while(fscanf(fp, "%s", buf) != EOF){
			N ++;
		}
		fclose(fp);			
	}
	return N;
}


// Make string to integer so that can know the index of url in list
int searchURL(char *URL, char **urllist, int numofurl){	
	int i;
	
	for (i = 0; i < numofurl; i++){
		// Check if urls are repetitive
		if (strcmp(URL, urllist[i]) == 0){
			return i;
		}
	}
	return -1;
}

// Draw the graph
void ExchangeToGraph(Graph g, char **urllist, int numberofurl){
	int i, count;
	char urlFileName[MAX_LINE], txtFileName[MAX_LINE], buf[MAX_LINE];
	FILE *fp;            
	char str[10], *url[10];
	Edge e;
	
	for(i = 0; i < numberofurl; i ++){
		strcpy(urlFileName, urllist[i]);	// copy the current url
		strcpy(txtFileName, urllist[i]);	
		strcat(txtFileName, ".txt");		// add ".txt" at the end
		if ((fp = fopen(txtFileName, "r")) == NULL) {
			perror("FAIL");
			exit (1);
		} else { 			
				count = 0;
				while (fscanf(fp, "%s", buf) != EOF){
					// operate the content between "Section-1" and "#end"
					if (strcmp(buf, "Section-1") == 0 || strcmp(buf, "#end") == 0){
						count++;
						continue;
					}
					// once "#end" shows, break
					if (count == 2){
						break;
					}
					// once "Section-1" shows, draw the graph 
					if (count == 1){
						e.v = searchURL(urlFileName, urllist, numberofurl);
//						printf("%s\n", urlFileName);
//						printf("v:%d\n", e.v);
						e.w = searchURL(buf, urllist, numberofurl);
//						printf("%s\n", buf);
//						printf("w:%d\n", e.w);
						insertEdge(g, e);
					}
				}		
		}
	}
}

// Compute the result of pagerank according to the formula given in assignment
/*			
			PageRank(d, diffPR, maxIterations)

			Read "web pages" from the collection in file "collection.txt"
			and build a graph structure using Adjacency List Representation

			N = number of urls in the collection
			For each url pi in the collection
				
			End For

			iteration = 0;
			diff = diffPR;   // to enter the following loop

			While (iteration < maxIteration AND diff >= diffPR)
				iteration++;
*/
void computeRankResult(int maxIterations, float d, float diffPR, Graph graph, int *numOfDegrees, double *rank){	
	int i, j;
	int iteration = 0;
	float diff;
	double initialPageRank[numOfVertices(graph)], currentPageRank[numOfVertices(graph)];
	
	i = 0;
	while (i < numOfVertices(graph)){
		i++;
		currentPageRank[i] = 1.0 / numOfVertices(graph);
	}
	
	do {
		iteration ++;
		diff = 0.0;
		for (i = 0; i < numOfVertices(graph); i++){	
			initialPageRank[i] = (1.0 - d) / numOfVertices(graph);
			for (j = 0; j < numOfVertices(graph); j++){
				if (adjacent(graph, j, i) && i != j){
					initialPageRank[i] += currentPageRank[j] / numOfDegrees[j] * d;
				}
			}
		}
		
		for (i = 0; i < numOfVertices(graph); i++){
			diff += fabs(initialPageRank[i] - currentPageRank[i]);
			currentPageRank[i] = initialPageRank[i];
			rank[i] = currentPageRank[i];
		}
	} while (diff > diffPR && iteration < maxIterations);	 
}


int main(int argc, char *argv[])
{
	int i, n, j, itemp;
	int numOfUrl = ReadCollection();
	int degree[numOfUrl], sortedRank[numOfUrl];
	int maxIteration = atoi(argv[3]);		// maxIteration = 1000
	double rank[numOfUrl], lftemp; 
	float d = atof(argv[1]), diffPR = atof(argv[2]) / 100;		// d =0.85,  diffPR = 0.00001 
	char *urlList[numOfUrl];
	Graph graph = newGraph(numOfUrl);
	FILE *fp, *fpw;
	
	for(i = 0; i < numOfUrl; i++){
		urlList[i] = malloc(100 * sizeof(char));
	}
	
	if ((fp = fopen("collection.txt","r")) == NULL){
			perror("FAIL");
			exit (1);
		} else {
			for(i = 0; i < numOfUrl; i++){
				fscanf(fp, "%s", urlList[i]);
				sortedRank[i] = i;
			}			
			fclose(fp);
		}
	// Draw the graph
	ExchangeToGraph(graph, urlList, numOfUrl);	
	
	// Get the number of the out-degree of url
	int numOfDegrees[numOfUrl];
	for (i = 0; i < numOfUrl; i++){
		numOfDegrees[i] = getNumberOfOutDegrees(graph, i);
	}
	
	// Compute pagerank				
	computeRankResult(maxIteration, d, diffPR, graph, numOfDegrees, rank);
		
	// Sort the pagerank according from high to low
	for (i = 0; i < numOfUrl; i++){
		for (j = 0; j < numOfUrl - i; j++){
			if (rank[j] < rank[j + 1]){
				lftemp = rank[j];
				rank[j] = rank[j + 1];
				rank[j + 1] = lftemp;
				itemp = sortedRank[j];
				sortedRank[j] = sortedRank[j + 1];
				sortedRank[j + 1] = itemp;
			}
		}
	}	
	
	// Write the data to pagerankList.txt
	if ((fpw = fopen("pagerankList.txt","w")) == NULL){
				perror("FAIL");
				exit (1);
			} else {
				for (i = 0; i < numOfUrl; i++){
					numOfDegrees[i] = getNumberOfOutDegrees(graph, i);
					n = sortedRank[i];
//					printf("%s, %d, %.7f\n", urlList[n], numOfDegrees[n], rank[i]);
					fprintf(fpw, "%s, %d, %.7f\n", urlList[n], numOfDegrees[n], rank[i]);
				}
				fclose(fpw);
			}	
	// free the graph
	freeGraph(graph);	
	
	return 0;		
}

