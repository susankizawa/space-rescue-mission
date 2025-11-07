#include "logger.h"

#include "config.h"
#include "utils.h"

#include <fstream>
#include <cstdio>
#include <cstdarg>
#include <cstring>
 
const char logsPath[] = "../logs/";
char filePath[MAX_PATH_LENGTH];

std::ofstream currentSessionLog;

LogMessage newLogMessage(const char timestamp[], const char prefix[], const char message[]) {
  LogMessage newLogMsg;
  strcpy(newLogMsg.timestamp, timestamp);
  strcpy(newLogMsg.prefix, prefix);
  strcpy(newLogMsg.message, message);
  sprintf(newLogMsg.fullMessage, "[%s] [%s]: %s\n", timestamp, prefix, message);
  return newLogMsg;
}

void initializeLogger() {
  if(ENABLE_LOGGER){
    char currentTimestamp[MAX_TIMESTAMP_LENGTH];
    getCurrentTimestamp("%d-%m-%Y", currentTimestamp, MAX_TIMESTAMP_LENGTH);
    sprintf(filePath, "%s%s.log", logsPath, currentTimestamp);
    currentSessionLog.open(filePath, std::ios::app);
    info("Logger initialized!");
  } else {
    printf("Logger is disabled.");
  }
}

LogMessage buildMessage(const char* prefix, const char* format, va_list args) {
  char buffer[MAX_MESSAGE_LENGTH];
  char currentTimestamp[MAX_TIMESTAMP_LENGTH];

  vsnprintf(buffer, sizeof(buffer), format, args);

  LogMessage msg;

  getCurrentTimestamp("%H:%M:%S", currentTimestamp, MAX_TIMESTAMP_LENGTH);

  strcpy(msg.timestamp, currentTimestamp);
  strcpy(msg.prefix, prefix);
  strcpy(msg.message, buffer);

  sprintf(msg.fullMessage, "[%s] [%s]: %s\n", msg.timestamp, msg.prefix, msg.message);

  return msg;
}

void handleLogOutput(char message[]) {
  if(ENABLE_DEBUG_MODE) {
    printf("%s", message);
  }

  if(ENABLE_LOGGER) {
    if (!currentSessionLog.is_open()){
      return;
    }

    currentSessionLog << message;
    currentSessionLog.flush();
  }
}

void log(const char* prefix, const char* format, ...) {
  va_list args;
  va_start(args, format);
  LogMessage msg = buildMessage(prefix, format, args);
  handleLogOutput(msg.fullMessage);
  va_end(args);
}

void info(const char* format, ...) {
  if(SILENCE_INFO)
    return;

  va_list args;
  va_start(args, format);
  LogMessage msg = buildMessage("INFO", format, args);
  handleLogOutput(msg.fullMessage);
  va_end(args);
}

void error(const char* format, ...) {
  va_list args;
  va_start(args, format);
  LogMessage msg = buildMessage("ERROR", format, args);
  handleLogOutput(msg.fullMessage);
  va_end(args);
}

void warning(const char* format, ...) {
  va_list args;
  va_start(args, format);
  LogMessage msg = buildMessage("WARNING", format, args);
  handleLogOutput(msg.fullMessage);
  va_end(args);
}

void debug(const char* format, ...) {
  va_list args;
  va_start(args, format);
  LogMessage msg = buildMessage("DEBUG", format, args);
  handleLogOutput(msg.fullMessage);
  va_end(args);
}

void append(const char* format, ...) {
  char buffer[MAX_MESSAGE_LENGTH];

  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  handleLogOutput(buffer);
}

void clear() {
  currentSessionLog.close();
  currentSessionLog.open(filePath);
}

void cleanupLogger() {
  info("Cleaning up logger...");
  currentSessionLog.close();
}
