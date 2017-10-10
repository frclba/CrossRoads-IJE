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
    terminal_border();
    terminal_message("[ Starting GAME ]");
    terminal_message("--> Arquivo de Log: " + file_name + "\n");

    log_file.open(file_name);

    border_message("Begin Logging");

    log_file.flush();
}

/**
  Closes the current log file
*/

void Log::closeFile() {

    if( log_file.is_open() ) {
        terminal_message("[ Encerrando GAME ]");
        terminal_message("<-- Para eventuais mensagens de sistema, " +
                          std::string("conferir arquivo: ") + file_name);
        terminal_border();

        border_message("End Logging");

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

void Log::debug(std::string message) {

    if( DEBUG ) {
        log_message("DEBUG", message);
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

void Log::warning(std::string message) {

    log_message("WARN", message);
    log_file.flush();

}

/**
 Adds a new error entry to the log file
  \param msg the message to be added
*/

void Log::error(std::string message) {

    log_message("ERROR", message);
    log_file.flush();

}


/**
  Adds a new info entry to the log file
  \param msg the message to the added
*/

void Log::info(std::string message) {

    log_message("INFO", message);
    log_file.flush();

}


/**
  Adds a new jumpline to the current log file
  \param msg the message to be added after the jumpline
*/
void Log::jumpLine(std::string message) {

  log_file << std::endl;
  log_message("->", message);
  log_file.flush();

}

/**
    Prints log message in standard format
*/
void Log::log_message(std::string kind, std::string message) {

    if( log_file.is_open() ) {
        log_file << "[ " << kind << " ] " << message << "\n";
    }
    else {
        // Do nothing
    }

}

/**
    Prints border in the log file to mark the start or end of a new section
*/
void Log::border_message(std::string message) {

    if( log_file.is_open() ) {
        print_border();
        log_file << message << std::endl;
        print_border();
    }
    else {
        // Do nothing
    }

}

/**
    Print border
*/
void Log::print_border() {

    for(int index = 0; index < 80; index++) {
        log_file << "=";
    }
    log_file << std::endl;

}

/**
    Print border in the terminal to mark the start or end of a new section
*/
void Log::terminal_border() {

    for(int index = 0; index < 80; index++) {
        std::cout << "_";
    }
    std::cout << std::endl;
    std::cout << std::endl;

}

/**
    Print message in the terminal
*/
void Log::terminal_message(std::string message) {

    std::cout << message << std::endl;

}
