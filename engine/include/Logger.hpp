/**
  \file Logger.hpp
  this file contains the class Log and its member functions
*/

#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <string>
#include <iostream>

//Set 1 for debug messages, 0 to no show

#define DEBUG 1

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

    /**
      Filebuf that supports the input / output operations in the log file.
    */
    std::ofstream log_file;

    /**
      Log file name
      \note If the log file already exists in the folder it will be overwritten
    */
    std::string file_name = "";

    //Open and close stream file to be written

    void openFile();
    void closeFile();

};

#endif // LOGGER_H
