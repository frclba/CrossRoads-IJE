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

    file_name = "log.txt";
    std::cout << "__________________________________________________\n" <<
        "\n[ Starting GAME ]\n" <<
        "--> Arquivo de Log: " << file_name << std::endl << std::endl;

    log_file.open(file_name);

    std::string border =
    "==============================================================\n";
    std::string logMessage = "Begin Logging\n";

    log_file << border << logMessage << border;
    log_file.flush();
}

/**
  Closes the current log file
*/

void Log::closeFile() {

    if( log_file.is_open() ) {
        std::cout << "[ Encerrando GAME ]\n" <<
        "<-- Para eventuais mensagens de sistema,\nconferir arquivo: " <<
        file_name << std::endl <<
        "__________________________________________________\n" << std::endl;

        std::string border =
        "==============================================================\n";
        std::string logMessage = "End Logging\n";

        log_file << border << logMessage << border;
        log_file.flush();
        log_file.close();
    }
    else {
        // Do nothing
    }

}

/**
  Adds a debug entry to the current log file
  \param msg the message to be added to the log file
*/

void Log::debug(std::string msg) {

    if( DEBUG ) {
        log_file << "[DEBUG] ";
        log_file << msg << std::endl;
        log_file.flush();
    }
    else {
        // Do nothing
    }

}

/**
  Adds a new warning entry to the log file
  \param msg the warning message to be added
*/

void Log::warning(std::string msg) {

    log_file << "[WARN] ";
    log_file << msg << std::endl;
    log_file.flush();

}

/**
 Adds a new error entry to the log file
  \param msg the message to be added
*/

void Log::error(std::string msg) {

    log_file << "[ERROR] ";
    log_file << msg << std::endl;
    log_file.flush();

}


/**
  Adds a new info entry to the log file
  \param msg the message to the added
*/

void Log::info(std::string msg) {

    log_file << "[INFO] ";
    log_file << msg << std::endl;
    log_file.flush();

}


/**
  Adds a new jumpline to the current log file
  \param msg the message to be added after the jumpline
*/
void Log::jumpLine(std::string msg) {

  log_file << "\n[->]";
  log_file << msg << std::endl;
  log_file.flush();

}
