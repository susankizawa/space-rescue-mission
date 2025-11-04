#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <string>
#include <vector>

#include "stationNetwork.h"

void removeWhitespace(std::string& s);

std::vector<std::string> getFields(const std::string& line);

std::vector<Station> loadNetworkData(const std::string& filename, bool ignoreHeader = false);

#endif