#ifndef GRAPH_H
#define GRAPH_H

#include "config.h"

typedef struct Graph {
  int numVertices;
  int numEdges;
  int isDirectional;
  int adjMatrix[MAX_SIZE][MAX_SIZE];
} Graph;

typedef struct Path {
  int vertices[MAX_SIZE];
  int length;
} Path;

void initializeGraph(Graph* graph, int numVertices, int isDirectional);

void addVertex(Graph* graph);

void removeVertex(Graph* graph, int v);

int getEdgeWeight(Graph* graph, int u, int v);

void addEdge(Graph* graph, int u, int v, int weight = 1);

void removeEdge(Graph* graph, int u, int v);

void printMatrix(int matrix[][MAX_SIZE], int width, int height);

float getGraphDensity(Graph* graph);

void initializePath(Path* path);

int getOrigin(Path* path);

int getDestination(Path* path);

void printPath(Path* path);

#endif