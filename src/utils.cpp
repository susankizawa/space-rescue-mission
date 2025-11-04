#include "utils.h"

#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

std::string getCurrentTimestamp(const std::string& format) {
  auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), format.c_str());
    return ss.str();
}