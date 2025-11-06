#include "utils.h"

#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

void getCurrentTimestamp(const char format[], char buffer[], size_t bufferSize) {
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  strftime(buffer, bufferSize, format, std::localtime(&time));
}

int containsElement(int arr[], int size, int target) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == target) {
      return 1; // Element found
    }
  }
  return 0; // Element not found
}