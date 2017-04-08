#include "logger.hpp"

Log Log::instance;

Log::Log() {
    openFile();
}

Log::~Log() {
    closeFile();
}

// Open the log file with <date>_fileName.log or <date>.log
void Log::openFile() {

    fileName = "log.txt";
    std::cout << "Loading log file: " << fileName << std::endl;

    logFile.open(fileName);

    std::string border = "==============================================================\n";
    std::string logMessage = "Begin Logging\n";

    logFile << border << logMessage << border;
    logFile.flush();
}

// Close the currently open log file
void Log::closeFile() {
    if(logFile.is_open()) {
        std::cout << "Closing log file: " << fileName << std::endl;
        std::string border = "==============================================================\n";
        std::string logMessage = "End Logging\n";

        logFile << border << logMessage << border;
        logFile.flush();
        logFile.close();
    }
}

// Debug message
void Log::debug(std::string msg) {
    if (DEBUG) {
    logFile << "[DEBUG] ";
    logFile << msg << std::endl;
    logFile.flush();
    }
}

// Warning message
void Log::warning(std::string msg) {
    logFile << "[WARN] ";
    logFile << msg << std::endl;
    logFile.flush();
}

// Error message
void Log::error(std::string msg) {
    logFile << "[ERROR] ";
    logFile << msg << std::endl;
    logFile.flush();
}

void Log::info(std::string msg) {
    logFile << "[INFO]";
    logFile << msg << std::endl;
    logFile.flush();
}
