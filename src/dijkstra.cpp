#include "dijkstra.h"

#include "config.h"
#include "utils.h"
#include "logger.h"
#include "graph.h"

#include <climits>

int minDistance(int accumulatedDist[], int finalizedNodes[]) {
  int closestNode = INT_MAX;

  for(int i = 0; i < MAX_SIZE; i++) {
    // if node has already been finalized, skip it
    if(finalizedNodes[i]) 
      continue;
    
    if(accumulatedDist[i] < closestNode)
      closestNode = i;
  }

  return closestNode;
}

void dijkstra(Graph* graph, int path[], int* pathLengh, int origin, int destination) {
  int accumulatedDist[graph->numVertices];
  int finalizedNodes[graph->numVertices];
  int parent[graph->numVertices];
  int pathLength = 0;
  int v = destination;

  // initializing all nodes with infinite dist
  for(int i = 0; i < graph->numVertices; i++) {
    accumulatedDist[i] = INT_MAX;
    finalizedNodes[i] = 0;
  }

  // giving 0 dist to origin
  accumulatedDist[origin] = 0;
  parent[origin] = -1;

  // finding shortest paths
  for(int count = 0; count < graph->numVertices - 1; count++) {
    int closestNode = minDistance(accumulatedDist, finalizedNodes);
    finalizedNodes[closestNode] = 1;
    for(int v = 0; v < graph->numVertices; v++) {
      debug("closestNode = %d", closestNode);
      debug("getEdgeWeight(graph, closestNode, v) = %d", getEdgeWeight(graph, closestNode, v));
      if(finalizedNodes[v] == 1 || getEdgeWeight(graph, closestNode, v) == 0)
        continue;

      
      debug("accumulatedDist[v] = %d", accumulatedDist[v]);
      //debug("accumulatedDist[closestNode] + getEdgeWeight(graph, closestNode, v) = %d", accumulatedDist[closestNode] + getEdgeWeight(graph, closestNode, v));
      //if((accumulatedDist[closestNode] + getEdgeWeight(graph, closestNode, v)) < accumulatedDist[v]) {
        
      //  accumulatedDist[v] = accumulatedDist[closestNode] +  getEdgeWeight(graph, closestNode, v);
      //  parent[v] = closestNode;
      //}
    }
  }

  while(v != -1) {
    path[pathLength++] = v;
    
    v = parent[v];
  }
}

