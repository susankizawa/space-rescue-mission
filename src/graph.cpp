#include "graph.h"

#include <cstdio>
#include <string>
#include <sstream>

#include "logger.h"

void initializeGraph(Graph* graph, int numVertices, int isDirectional) {
  graph->numVertices = numVertices;
  graph->isDirectional = isDirectional;
  for(int i = 0; i < MAX_SIZE; i++) {
    for(int j = 0; j < MAX_SIZE; j++) {
      graph->adjMatrix[i][j] = 0;
    }
  }
}

void addEdge(Graph* graph, int u, int v) {
  graph->adjMatrix[u][v] = 1;
  if(!graph->isDirectional){
    graph->adjMatrix[v][u] = 1;
  }
}

void removeEdge(Graph* graph, int u, int v) {
  graph->adjMatrix[u][v] = 0;
  if(!graph->isDirectional) {
    graph->adjMatrix[v][u] = 0;
  }
}

void printMatrix(int matrix[][MAX_SIZE], int width, int height) {
  std::ostringstream msg;

  msg << "\n";

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      msg << "[" << matrix[i][j] << "]";
    }
    msg << "\n";
  }

  debug(msg.str());
}