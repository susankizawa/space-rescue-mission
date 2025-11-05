#include "dataLoader.h"

#include "config.h"
#include "logger.h"
#include "stationNetwork.h"

#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include <iostream>

std::vector<std::string> getFields(const std::string& line) {
  std::vector<std::string> fields;
  std::stringstream lineStream(line);
  std::string cell;
  while(std::getline(lineStream, cell, ',')) {
    fields.push_back(cell);
  }
  return fields;
}


std::vector<Station> loadNetworkData(const std::string& filename, bool ignoreHeader) {
  std::ifstream file(filename);
  
  if(!file.is_open()) {
    error("Could not open file: %s", filename);
    return {};
  }

  info("Loading data...");

  std::vector<Station> stations;
  std::string line;
  unsigned int lineCounter = 0;
  file.seekg(0);

  if(ignoreHeader) {
    std::getline(file, line);
    lineCounter++;
  }

  while(std::getline(file, line)) {
    lineCounter++;

    if(line.empty()) continue;

    std::vector<std::string> fields = getFields(line);

    if(fields[0].empty()) {
      warning("Skipping line %d: Station name is required but missing.", lineCounter);
      continue;
    }

    if (fields.size() > 1 && (fields.size() % 2) == 0) {
      warning("Skipping line %d: Inconsistent number of fields. Expected a pair of destination and weight.", lineCounter);
      continue;
    }

    Station station;
    std::string stationStr = fields[0];
    strncpy(station.name, stationStr.c_str(), MAX_STATION_NAME_LENGTH);

    for(int i = 1; i < fields.size(); i += 2) {
      Connection newConn;
      std::string destination = fields[i];
      std::string weightStr = fields[i + 1];
      int weight;

      if(destination.empty()) {
        warning("Skipping line %d: Malformed connection: Destination station name is empty.", lineCounter);
        continue;
      }

      if(weightStr.empty()) {
        warning("Skipping line %d: Malformed connection: Weight is empty.", lineCounter);
        continue;
      }

      strncpy(newConn.destination, destination.c_str(), MAX_STATION_NAME_LENGTH);

      try {
        weight = std::stoi(weightStr);
        newConn.weight = weight;
      } catch (const std::invalid_argument& e) {
        warning("Skipping line %d: Couldn't convert weight to int on connection to %s.", lineCounter, destination);
        continue;
      } catch (const std::out_of_range& e) {
        warning("Skipping line %d: Weight out of range on connection to %d.", lineCounter, destination);
        continue;
      }
      station.connections.push_back(newConn);
    }
    stations.push_back(station);
  }

  if(stations.empty()) {
    info("Could not find any stations.");
  }
  else {
    info("Finished loading data!");
  }

  return stations;
}