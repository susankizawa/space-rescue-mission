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
  printf("Matriz de adjacências das rotas:\n");
  printf("%10.10s\t", "");  // empty corner
  for(int i = 0; i < numStations; i++) {
    printf("%-10.10s\t", stations[i]);
  }
  printf("\n");
  for(int i = 0; i < numStations; i++) {
    // vertical header row
    printf("%10.10s\t", stations[i]);
    // route connections
    for(int j = 0; j < numStations; j++){
      printf("%-10d\t", routes.adjMatrix[i][j]);
    }
    printf("\n");
  }
}

void printStationNetworkInfo(StationNetwork* stationNetwork) {
  auto& routes = stationNetwork->routes;
  auto& numStations = routes.numVertices;
  auto& numRoutes = routes.numEdges;
  auto& stations = stationNetwork->stations;
  float networkDensity = getGraphDensity(&routes);

  printf("Informações da rede espacial:\n");
  printf("Número de estações: %d\n", numStations);
  printf("Número de rotas: %d\n", numRoutes);
  printf("Densidade da rede: %.3f\n", networkDensity);
  printf("Nível de conectividade: ");
  if(networkDensity > 0.5)
    printf("Densa\n");
  else
    printf("Esparsa\n");
  printf("Estações: ");
  for(int i = 0; i < numStations - 1; i++) {
    printf("%s, ", stations[i]);
  }
  printf("%s\n", stations[numStations - 1]);
}
 
int getStationIndex(StationNetwork* stationNetwork, const char stationName[]) {
  auto& numStations = stationNetwork->routes.numVertices;
  auto& stations = stationNetwork->stations;
  for(int i = 0; i < numStations; i++){
    if(strcmp(stations[i], stationName) == 0)
      return i;
  }
  //warning("Couldn't find station %s.", stationName);
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

bool addRoute(StationNetwork* stationNetwork, const char origin[], const char destination[], int weight) {
  auto& routes = stationNetwork->routes;
  int originIndex = getStationIndex(stationNetwork, origin);
  int destinationIndex = getStationIndex(stationNetwork, destination);

  if(originIndex == -1) {
    error("Couldn't find origin station %s.", origin);
    return false;
  }
  if(destinationIndex == -1) {
    error("Couldn't find destination station %s.", destination);
    return false;
  }

  addEdge(&routes, originIndex, destinationIndex, weight);
  info("Added route from %s to %s.", origin, destination);
  return true;
}
 
bool removeRoute(StationNetwork* stationNetwork, const char origin[], const char destination[]) {
  auto& routes = stationNetwork->routes;
  int originIndex = getStationIndex(stationNetwork, origin);
  int destinationIndex = getStationIndex(stationNetwork, destination);

  if(originIndex == -1) {
    error("Couldn't find origin station %s.", origin);
    return false;
  }
  if(destinationIndex == -1) {
    error("Couldn't find destination station %s.", destination);
    return false;
  }

  removeEdge(&routes, originIndex, destinationIndex);
  info("Removed route from %s to %s.", origin, destination);
  return true;
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

  if(originIndex == -1) {
    error("Couldn't find origin station %s.", origin);
    return;
  }
  if(destinationIndex == -1) {
    error("Couldn't find destination station %s.", destination);
    return;
  }

  dijkstra(&stationNetwork->routes, path, originIndex, destinationIndex);
}

void printStationPath(StationNetwork* stationNetwork, Path* path) {
  auto& stations = stationNetwork->stations;
  auto& length = path->length;
  auto& vertices = path->vertices;

  if(path->length == 0) {
    printf("Vazio");
    return;
  }

  for(int i = 0; i < length - 1; i++) {
    printf("%s -> ", stations[vertices[i]]);
  }
  printf("%s\n", stations[vertices[length - 1]]);
}