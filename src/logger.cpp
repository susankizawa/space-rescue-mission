#include "logger.h"

#include <fstream>
#include <cstdio>
#include <string>

#include "config.h"
#include "utils.h"

const std::string logsPath = "../logs/";
std::string filePath;

std::ofstream currentSessionLog;

LogMessage newLogMessage(std::string timestamp, std::string prefix, std::string message) {
  LogMessage newLogMsg;
  newLogMsg.timestamp = timestamp;
  newLogMsg.prefix = prefix;
  newLogMsg.message = message;
  newLogMsg.fullMessage = "[" + timestamp + "] [" + prefix + "]: " + message + "\n";
  return newLogMsg;
}

void initializeLogger() {
  if(ENABLE_LOGGER){
    filePath = logsPath + getCurrentTimestamp("%d-%m-%Y") + ".log";
    currentSessionLog.open(filePath.c_str(), std::ios::app);
  }
  log("Logger initialized!");
}

void log(const std::string& message) {
  LogMessage logMsg = newLogMessage(getCurrentTimestamp("%H:%M:%S"), "LOG", message);

  if(ENABLE_DEBUG_MODE) {
    printf(logMsg.fullMessage.c_str());
  }

  if(ENABLE_LOGGER) {
    currentSessionLog << logMsg.fullMessage;
  }
}

void info(const std::string& message) {
  LogMessage logMsg = newLogMessage(getCurrentTimestamp("%H:%M:%S"), "INFO", message);

  if(ENABLE_DEBUG_MODE) {
    printf(logMsg.fullMessage.c_str());
  }

  if(ENABLE_LOGGER) {
    currentSessionLog << logMsg.fullMessage;
  }
}

void error(const std::string& message) {
  LogMessage logMsg = newLogMessage(getCurrentTimestamp("%H:%M:%S"), "ERROR", message);

  if(ENABLE_DEBUG_MODE) {
    printf(logMsg.fullMessage.c_str());
  }

  if(ENABLE_LOGGER) {
    currentSessionLog << logMsg.fullMessage;
  }
}

void warning(const std::string& message) {
  LogMessage logMsg = newLogMessage(getCurrentTimestamp("%H:%M:%S"), "WARNING", message);

  if(ENABLE_DEBUG_MODE) {
    printf(logMsg.fullMessage.c_str());
  }

  if(ENABLE_LOGGER) {
    currentSessionLog << logMsg.fullMessage;
  }
}

void debug(const std::string& message) {
  LogMessage logMsg = newLogMessage(getCurrentTimestamp("%H:%M:%S"), "DEBUG", message);

  if(ENABLE_DEBUG_MODE) {
    printf(logMsg.fullMessage.c_str());
  }

  if(ENABLE_LOGGER) {
    currentSessionLog << logMsg.fullMessage;
  }
}

void clear() {
  currentSessionLog.close();
  currentSessionLog.open(filePath.c_str());
}

void cleanupLogger() {
    currentSessionLog.close();
}