#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>

class Logger {
public:
    Logger() : fileStream("log.txt") {
        fileStream.open("log.txt", std::ios::app);
    }

    ~Logger() {
        fileStream.close();
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex);
        fileStream << message << std::endl;
    }

    std::string readLine() {
        std::lock_guard<std::mutex> lock(mutex);
        std::string line;
        std::getline(fileStream, line);
        return line;
    }

private:
    std::ofstream fileStream;
    std::mutex mutex;
};

#endif // LOGGER_H