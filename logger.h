#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <stdexcept>

class Logger {
public:
    Logger(const std::string& filename = "log.txt") {
        fileStream.open(filename, std::ios::in | std::ios::out | std::ios::app);
        if (!fileStream.is_open()) {
            throw std::runtime_error("Unable to open log file: " + filename);
        }
    }

    ~Logger() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex);
        if (fileStream.is_open()) {
            fileStream << message << std::endl;
            if (fileStream.fail()) {
                throw std::runtime_error("Failed to write to log file");
            }
        } else {
            throw std::runtime_error("Log file is not open");
        }
    }

    std::string readLine() {
        std::lock_guard<std::mutex> lock(mutex);
        if (fileStream.is_open()) {
            std::string line;
            if (std::getline(fileStream, line)) {
                return line;
            } else if (fileStream.eof()) {
                return ""; // End of file reached
            } else {
                throw std::runtime_error("Failed to read from log file");
            }
        } else {
            throw std::runtime_error("Log file is not open");
        }
    }

private:
    std::fstream fileStream;
    std::mutex mutex;
};

#endif // LOGGER_H
