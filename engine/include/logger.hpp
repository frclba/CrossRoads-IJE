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
    Log();
    ~Log();
    Log(std::string fileName);

    void openFile();
    void closeFile();

    void debug(std::string message);
    void warning(std::string message);
    void error(std::string message);
    void info(std::string message);

private:
    std::ofstream logFile;
    std::string fileName;
};

#endif
