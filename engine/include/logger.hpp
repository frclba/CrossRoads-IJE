#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <string>
#include <iostream>

//Set 1 for debug messages

//Define DEBUG 1

//TODO -> write function to write time into logfile.txt

class Log {
public:
    static Log instance;

    void debug(std::string message);
    void warning(std::string message);
    void error(std::string message);
    void info(std::string message);

private:
    Log();
    ~Log();

    std::ofstream logFile;
    std::string fileName;

    void openFile();
    void closeFile();
};

#endif
