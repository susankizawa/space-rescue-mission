#ifndef LOGGER_H
#define LOGGER_H

#include "config.h"

#include <fstream>

#define MAX_TIMESTAMP_LENGTH 20
#define MAX_PREFIX_LENGTH 20
#define MAX_MESSAGE_LENGTH 512
#define MAX_FULL_MESSAGE_LENGTH (MAX_TIMESTAMP_LENGTH + MAX_PREFIX_LENGTH + MAX_MESSAGE_LENGTH + 10)
#define MAX_PATH_LENGTH 1024

typedef struct LogMessage {
  char timestamp[MAX_TIMESTAMP_LENGTH];
  char prefix[MAX_PREFIX_LENGTH];
  char message[MAX_MESSAGE_LENGTH];
  char fullMessage[MAX_FULL_MESSAGE_LENGTH];

} LogMessage;

LogMessage newLogMessage(const char timestamp[], const char prefix[], const char message);

void initializeLogger();

void log(const char* prefix, const char* format, ...);

void info(const char* format, ...);

void error(const char* format, ...);

void warning(const char* format, ...);

void debug(const char* format, ...);

void append(const char* format, ...);

void clear();

void cleanupLogger();

#endif