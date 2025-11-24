#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <string>
#include <vector>

#include "stationNetwork.h"

std::vector<Station> loadNetworkData(const std::string& filename, bool ignoreHeader = false);

#endif