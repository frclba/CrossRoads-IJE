#include "logger.hpp"


Log::Log() {
    openFile();
}

Log::Log(std::string file): fileName(file) {
    openFile();
}

Log::~Log() {
    closeFile();
}

// Open the log file with <date>_fileName.log or <date>.log
void Log::openFile() {
    time_t rawtime;
    struct tm* timeinfo;
    char buffer [80];
    time(&rawtime);
    logger_time = rawtime;
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%F",timeinfo);
    fileName = std::string(buffer) + (fileName.size()?"_":"") + fileName + ".log";
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

// Print the time string
// Also checks for a new day to open a new log
std::string Log::print_time() {
    struct tm* timeinfo;
    time_t t;
    time(&t);
    // Check time
    double diff_seconds = difftime(t,logger_time);
    // If greater than a day old, open a new one.
    if (diff_seconds >= 86400) {
        closeFile();
        openFile();
    }
    char buffer[80];
    timeinfo = localtime(&t);
    strftime(buffer,80,"[%c]",timeinfo);
    return buffer;
}

// Debug message
void Log::d(std::string msg) {
    //if (DEBUG) {
    	logFile << print_time();
        logFile << "[DEBUG] ";
        logFile << msg << std::endl;
        logFile.flush();
    //}
}

// Warning message
void Log::w(std::string msg) {
    logFile << print_time();
    logFile << "[WARN] ";
    logFile << msg << std::endl;
    logFile.flush();
}

// Error message
void Log::e(std::string msg) {
    logFile << print_time();
    logFile << "[ERROR] ";
    logFile << msg << std::endl;
    logFile.flush();
}
