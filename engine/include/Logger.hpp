/**
  \file Logger.hpp
  this file contains the class Log and its member functions
*/

#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <string>
#include <iostream>
#include <assert.h>

//Set 1 for debug messages, 0 to no show

#define DEBUG 1
#define LINE_LIMIT 80

/*
  TODO -> write function to write time into logfile.txt
  TODO -> Apply log on Iniciando componente de imagem, Iniciando componente de
  animacao, Init game object
*/


/// Log class
/**
  \class Log
  The log class manages the logging system of the game
*/

class Log {

public:

    /**
      Log instance to keep the log file while playing the game
    */
    static Log instance;

    /* Functions to print on file according to type of message */

    void debug(std::string message);
    void warning(std::string message);
    void error(std::string message);
    void info(std::string message);
    void jumpLine(std::string message);

private:

    Log();
    ~Log();

    std::ofstream log_file;
    std::string file_name = "";

    //Open and close stream file to be written

    void openFile();
    void closeFile();
    void print_border();
    void terminal_border();
    void terminal_message(std::string message);
    void border_message(std::string message);
    void log_message(std::string kind, std::string message);

};

#endif // LOGGER_H
