#include "stationNetwork.h"

#include "logger.h"
#include "dijkstra.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <format>
#include <sstream>


void initializeStationNetwork(StationNetwork* stationNetwork) {
  info("Initializing station network...");
  initializeGraph(&stationNetwork->routes, 0, false);
  info("Station network initialized!");
}

void printStationNetwork(StationNetwork* stationNetwork){
  char msg[50];
  auto& numStations = stationNetwork->routes.numVertices;
  auto& stations = stationNetwork->stations;
  auto& routes = stationNetwork->routes;
  // horizontal header row
  debug("Routes adjacency matrix:");
  append("%10.10s\t", "");  // empty corner
  for(int i = 0; i < numStations; i++) {
    append("%-10.10s\t", stations[i]);
  }
  append("\n");
  for(int i = 0; i < numStations; i++) {
    // vertical header row
    append("%10.10s\t", stations[i]);
    // route connections
    for(int j = 0; j < numStations; j++){
      append("%-10d\t", routes.adjMatrix[i][j]);
    }
    append("\n");
  }
}

void printStationNetworkInfo(StationNetwork* stationNetwork) {
  auto& routes = stationNetwork->routes;
  auto& numStations = routes.numVertices;
  auto& numRoutes = routes.numEdges;
  auto& stations = stationNetwork->stations;
  float networkDensity = getGraphDensity(&routes);

  debug("Station network info:");
  append("Number of stations: %d\n", numStations);
  append("Number of routes: %d\n", numRoutes);
  append("Network density: %.3f\n", networkDensity);
  append("Level of connectivity: ");
  if(networkDensity > 0.5)
    append("Dense\n");
  else
    append("Sparse\n");
  append("Stations: ");
  for(int i = 0; i < numStations - 1; i++) {
    append("%s, ", stations[i]);
  }
  append("%s\n", stations[numStations - 1]);
}
 
int getStationIndex(StationNetwork* stationNetwork, const char stationName[]) {
  auto& numStations = stationNetwork->routes.numVertices;
  auto& stations = stationNetwork->stations;
  for(int i = 0; i < numStations; i++){
    if(strcmp(stations[i], stationName) == 0)
      return i;
  }
  warning("Couldn't find station %s.", stationName);
  return -1;
}

void addStation(StationNetwork* stationNetwork, const char stationName[]) {
  auto& numStations = stationNetwork->routes.numVertices;
  auto& stations = stationNetwork->stations;
  auto& routes = stationNetwork->routes;
  strcpy(stations[numStations++], stationName);
  routes.numVertices = numStations;
  info("Added station %s.", stationName);
}

void addRoute(StationNetwork* stationNetwork, const char origin[], const char destination[], int weight) {
  auto& routes = stationNetwork->routes;
  int originIndex = getStationIndex(stationNetwork, origin);
  int destinationIndex = getStationIndex(stationNetwork, destination);
  addEdge(&routes, originIndex, destinationIndex, weight);
  info("Added route from %s to %s.", origin, destination);
}
 
void removeRoute(StationNetwork* stationNetwork, const char origin[], const char destination[]) {
  auto& routes = stationNetwork->routes;
  int originIndex = getStationIndex(stationNetwork, origin);
  int destinationIndex = getStationIndex(stationNetwork, destination);
  removeEdge(&routes, originIndex, destinationIndex);
  info("Removed route from %s to %s.", origin, destination);
}

void cleanupStationNetwork(StationNetwork* stationNetwork) {
  free(stationNetwork);
  info("Station network freed!");
}

void buildNetworkFromData(StationNetwork* stationNetwork, std::vector<Station> stations) {
  info("Building station network...");

  for(int i = 0; i < stations.size(); i++) {
    addStation(stationNetwork, stations[i].name);
  }

  for(int i = 0; i < stations.size(); i++) {
    Station origin = stations[i];
    for(int j = 0; j < origin.connections.size(); j++) {
      Connection connection = origin.connections[j];
      addRoute(stationNetwork, origin.name, connection.destination, connection.weight);
    }
  }
}

void getShortestStationPath(StationNetwork* stationNetwork, Path* path, const char origin[], const char destination[]) {
  int originIndex = getStationIndex(stationNetwork, origin);
  int destinationIndex = getStationIndex(stationNetwork, destination);
  dijkstra(&stationNetwork->routes, path, originIndex, destinationIndex);
  
}

void printStationPath(StationNetwork* stationNetwork, Path* path) {
  auto& stations = stationNetwork->stations;
  auto& length = path->length;
  auto& vertices = path->vertices;

  debug("Path:");
  for(int i = length - 1; i > 0; i--) {
    append("%s -> ", stations[vertices[i]]);
  }
  append("%s\n", stations[vertices[0]]);
}