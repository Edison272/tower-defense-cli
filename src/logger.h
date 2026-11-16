//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <queue>

// Implement the following methods:
// Log
// Flush
// Message format is "2024-08-30 14:48:16 Starting game..."

class Logger {
   public:
    static Logger& GetInstance();

    ~Logger();
    void Log(std::string message);  // add messages to the logQueue
    void Flush();  // go through queue and write remaining logs to file

   private:
    Logger();

    std::ofstream logFile;
    std::thread logThread;  // keep logging on a seperate thread
    std::queue<std::string> logQueue;
    bool exitFlag = false;

    void ProcessLogs();
    std::string GetCurrentTimestamp();
};

#endif  // LOGGER_H
