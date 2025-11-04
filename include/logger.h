#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

typedef struct LogMessage {
  std::string timestamp;
  std::string prefix;
  std::string message;
  std::string fullMessage;
} LogMessage;

extern std::ofstream currentSessionLog;

LogMessage newLogMessage(std::string timestamp, std::string prefix, std::string message);

void initializeLogger();

void log(const std::string& message);

void info(const std::string& message);

void error(const std::string& message);

void warning(const std::string& message);

void debug(const std::string& message);

void clear();

void cleanupLogger();

#endif