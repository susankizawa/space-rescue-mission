#ifndef STATION_NETWORK_H
#define STATION_NETWORK_H

#include "config.h"
#include "graph.h"

#include <vector>

#define MAX_STATION_NAME_LENGTH 50

typedef struct StationNetwork {
  int numStations;
  char stations[MAX_SIZE][MAX_STATION_NAME_LENGTH];
  Graph routes;
} StationNetwork;

typedef struct Connection {
  char destination[MAX_STATION_NAME_LENGTH];
  int weight;
} Connection;

typedef struct Station {
  char name[MAX_STATION_NAME_LENGTH];
  std::vector<Connection> connections;
} Station;

void initializeStationNetwork(StationNetwork* stationNetwork);
 
void printStationNetwork(StationNetwork* stationNetwork);
 
void printStationNetworkInfo(StationNetwork* stationNetwork);
 
int getStationIndex(StationNetwork* stationNetwork, const char stationName[]);
 
void addStation(StationNetwork* stationNetwork, const char stationName[]);
 
void addRoute(StationNetwork* stationNetwork, const char origin[], const char destination[]);
 
void removeRoute(StationNetwork* stationNetwork, const char origin[], const char destination[]);

void cleanupStationNetwork(StationNetwork* stationNetwork);

void buildNetworkFromData(StationNetwork* stationNetwork, std::vector<Station> stations);

#endif