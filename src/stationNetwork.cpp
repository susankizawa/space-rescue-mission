#include "stationNetwork.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <format>
#include <sstream>

#include "logger.h"

void initializeStationNetwork(StationNetwork* stationNetwork) {
  stationNetwork->numStations = 0;
  initializeGraph(&stationNetwork->routes, stationNetwork->numStations, false);
}

void printStationNetwork(StationNetwork* stationNetwork){
  std::ostringstream msg;
  auto& numStations = stationNetwork->numStations;
  auto& stations = stationNetwork->stations;
  auto& routes = stationNetwork->routes;
  // horizontal header row
  msg << "\n,\t";  // empty corner
  for(int i = 0; i < numStations; i++) {
    msg << stations[i] << ","; 
  }
  msg << "\n";
  for(int i = 0; i < numStations; i++) {
    // vertical header row
    msg << stations[i] << ",";
    // route connections
    for(int j = 0; j < numStations; j++){
      msg << routes.adjMatrix[i][j] << ",";
    }
    msg << "\n";
  }

  debug(msg.str());
}

void printStationNetworkInfo(StationNetwork* stationNetwork) {
  std::ostringstream msg;
  auto& numStations = stationNetwork->numStations;
  auto& stations = stationNetwork->stations;

  msg << "\nNumber of stations: " << stationNetwork->numStations << "\n";
  msg << "Stations: ";
  for(int i = 0; i < stationNetwork->numStations - 1; i++) {
    msg << stations[i] << ", ";
  }
  msg << stations[numStations - 1] << "\n";

  debug(msg.str());
}
 
int getStationIndex(StationNetwork* stationNetwork, const char* stationName) {
  auto& numStations = stationNetwork->numStations;
  auto& stations = stationNetwork->stations;
  for(int i = 0; i < numStations; i++){
    if(strcmp(stations[i], stationName) == 0)
      return i;
  }
  return -1;
}

void addStation(StationNetwork* stationNetwork, const char* stationName) {
  auto& numStations = stationNetwork->numStations;
  auto& stations = stationNetwork->stations;
  auto& routes = stationNetwork->routes;
  strcpy(stations[numStations++], stationName);
  routes.numVertices = numStations;
}

void addRoute(StationNetwork* stationNetwork, const char* origin, const char* destination) {
  auto& routes = stationNetwork->routes;
  int originIndex = getStationIndex(stationNetwork, origin);
  int destinationIndex = getStationIndex(stationNetwork, destination);
  addEdge(&routes, originIndex, destinationIndex);
}
 
void removeRoute(StationNetwork* stationNetwork, const char* origin, const char* destination) {
  auto& routes = stationNetwork->routes;
  int originIndex = getStationIndex(stationNetwork, origin);
  int destinationIndex = getStationIndex(stationNetwork, destination);
  removeEdge(&routes, originIndex, destinationIndex);
}

void cleanupStationNetwork(StationNetwork* stationNetwork) {
  free(stationNetwork);
}

void buildNetworkFromData(StationNetwork* stationNetwork, std::vector<Station> stations) {
  for(int i = 0; i < stations.size(); i++) {
    addStation(stationNetwork, stations.at(i).name.c_str());
  }

  for(int i = 0; i < stations.size(); i++) {
    Station currentStation = stations.at(i);
    for(int j = 0; j < currentStation.connections.size(); j++) {
      addRoute(stationNetwork, currentStation.name.c_str(), currentStation.connections.at(j).destination.c_str());
    }
  }
}