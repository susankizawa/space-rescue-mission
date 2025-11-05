#include "graph.h"

#include <cstdio>
#include <string>
#include <sstream>

#include "logger.h"

void initializeGraph(Graph* graph, int numVertices, int isDirectional) {
  info("Initializing graph...");
  graph->numVertices = numVertices;
  graph->isDirectional = isDirectional;
  for(int i = 0; i < MAX_SIZE; i++) {
    for(int j = 0; j < MAX_SIZE; j++) {
      graph->adjMatrix[i][j] = 0;
    }
  }
  info("Graph initialized!");
}

void addEdge(Graph* graph, int u, int v, int weight) {
  graph->adjMatrix[u][v] = weight;
  if(!graph->isDirectional){
    graph->adjMatrix[v][u] = weight;
  }
}

void removeEdge(Graph* graph, int u, int v) {
  graph->adjMatrix[u][v] = 0;
  if(!graph->isDirectional) {
    graph->adjMatrix[v][u] = 0;
  }
}

void printMatrix(int matrix[][MAX_SIZE], int width, int height) {
  debug("Matrix:");
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      append("[ %-3d ]", matrix[i][j]);
    }
    append("\n");
  }
}