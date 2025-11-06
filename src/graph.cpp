#include "graph.h"

#include "config.h"
#include "logger.h"

#include <cstdio>
#include <string>
#include <sstream>


void initializeGraph(Graph* graph, int numVertices, int isDirectional) {
  info("Initializing graph...");
  graph->numVertices = numVertices;
  graph->numEdges = 0;
  graph->isDirectional = isDirectional;
  for(int i = 0; i < MAX_SIZE; i++) {
    for(int j = 0; j < MAX_SIZE; j++) {
      graph->adjMatrix[i][j] = 0;
    }
  }
  info("Graph initialized!");
}

void addVertex(Graph* graph) {
  graph->numVertices++;
}

void removeVertex(Graph* graph, int v) {
  for(int i = 0; i < MAX_SIZE; i++) {
    graph->adjMatrix[v][i] = 0;
    graph->adjMatrix[i][v] = 0;
  }
}

int getEdgeWeight(Graph* graph, int u, int v) {
  return graph->adjMatrix[u][v];
}

void addEdge(Graph* graph, int u, int v, int weight) {
  graph->adjMatrix[u][v] = weight;
  if(!graph->isDirectional){
    graph->adjMatrix[v][u] = weight;
  }
  graph->numEdges++;
}

void removeEdge(Graph* graph, int u, int v) {
  graph->adjMatrix[u][v] = 0;
  if(!graph->isDirectional) {
    graph->adjMatrix[v][u] = 0;
  }
  graph->numEdges--;
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

float getGraphDensity(Graph* graph) {
  int v = graph->numVertices;
  int e = graph->numEdges;
  return (float) (2*e) / (v * (v - 1));
}