#include "dataLoader.h"

#include <string>
#include <vector>
#include <sstream>

#include "logger.h"
#include "stationNetwork.h"

std::vector<std::string> getFields(const std::string& line) {
  std::vector<std::string> fields;
  std::istringstream lineStream(line);
  std::string cell;
  while(std::getline(lineStream, cell, ',')) {
    fields.push_back(cell);
  }
  return fields;
}

std::vector<Station> loadNetworkData(const std::string& filename, bool ignoreHeader) {
  std::ifstream file(filename);
  
  if(!file.is_open()) {
    error("Could not open file: " + filename);
    return {};
  }

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

    if(fields.at(0).empty()) {
      warning("Skipping line " + std::to_string(lineCounter) + ": Station name is required but missing.");
      continue;
    }

    if (fields.size() > 1 && fields.size() % 2 == 0) {
      warning("Skipping line " + std::to_string(lineCounter) + ": Inconsistent number of fields. Expected a pair of destination and weight.");
      continue;
    }

    Station station;
    station.name = fields.at(0);

    for(int i = 1; i < fields.size(); i += 2) {
      Connection newConn;
      std::string destName = fields.at(i);
      std::string weightStr = fields.at(i + 1);

      if(destName.empty()) {
        warning("Skipping line " + std::to_string(lineCounter) + ": Malformed connection: Destination station name is empty.");
        continue;
      }

      if(weightStr.empty()) {
        warning("Skipping line " + std::to_string(lineCounter) + ": Malformed connection: Weight is empty.");
        continue;
      }

      try {
        int weight = std::stoi(weightStr);

        newConn.destination = destName;
        newConn.weight = weight;

        station.connections.push_back(newConn);
      } catch (const std::invalid_argument& e) {
        warning("Invalid weight format on line " + std::to_string(lineCounter) + ": for destination '" + destName + "' (" + std::string(e.what()) + ")");
        continue;
      } catch (const std::out_of_range& e) {
        warning("Weight out of range on line " + std::to_string(lineCounter) + ": for destination '" + destName + "' (" + std::string(e.what()) + ")");
        continue;
      }
    }

    stations.push_back(station);
  }

  return stations;
}