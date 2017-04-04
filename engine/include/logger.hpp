#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <string>
#include <iostream>

/*
Set to 1 for any DEBUG messages to be sent to the output
Set to 0 to remove only the DEBUG (logger.d()) messages from the log output
***Make sure to set this in your main file to get a DEBUG messages.

#define DEBUG 1

*/

//TODO -> write function to write time onto logfile.txt
class Log {
public:
    Log();
    ~Log();
    Log(std::string);
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
