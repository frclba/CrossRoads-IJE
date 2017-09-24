/**
  \file Logger.cpp
  This file contains implementations of methods related to the logging class
*/

#include "Logger.hpp"

Log Log::instance;

Log::Log() {

    openFile();

}

Log::~Log() {

    closeFile();

}

/**
  Opens a new log file
*/

void Log::openFile() {

    fileName = "log.txt";
    std::cout << "__________________________________________________\n" <<
        "\n[ Starting GAME ]\n" <<
        "--> Arquivo de Log: " << fileName << std::endl << std::endl;

    logFile.open(fileName);

    std::string border =
    "==============================================================\n";
    std::string logMessage = "Begin Logging\n";

    logFile << border << logMessage << border;
    logFile.flush();
}

/**
  Closes the current log file
*/

void Log::closeFile() {

    if( logFile.is_open() ) {
        std::cout << "[ Encerrando GAME ]\n" <<
        "<-- Para eventuais mensagens de sistema,\nconferir arquivo: " <<
        fileName << std::endl <<
        "__________________________________________________\n" << std::endl;

        std::string border =
        "==============================================================\n";
        std::string logMessage = "End Logging\n";

        logFile << border << logMessage << border;
        logFile.flush();
        logFile.close();
    }

}

/**
  Adds a debug entry to the current log file
  \param msg the message to be added to the log file
*/

void Log::debug(std::string msg) {

    if( DEBUG ) {
        logFile << "[DEBUG] ";
        logFile << msg << std::endl;
        logFile.flush();
    }

}

/**
  Adds a new warning entry to the log file
  \param msg the warning message to be added
*/

void Log::warning(std::string msg) {

    logFile << "[WARN] ";
    logFile << msg << std::endl;
    logFile.flush();

}

/**
 Adds a new error entry to the log file
  \param msg the message to be added
*/

void Log::error(std::string msg) {

    logFile << "[ERROR] ";
    logFile << msg << std::endl;
    logFile.flush();

}


/**
  Adds a new info entry to the log file
  \param msg the message to the added
*/

void Log::info(std::string msg) {

    logFile << "[INFO] ";
    logFile << msg << std::endl;
    logFile.flush();

}


/**
  Adds a new jumpline to the current log file
  \param msg the message to be added after the jumpline
*/
void Log::jumpLine(std::string msg) {

  logFile << "\n[->]";
  logFile << msg << std::endl;
  logFile.flush();

}
