#pragma once 

#include <string>
#include <mutex>
#include <fstream>
#include <iostream>
#include <filesystem>

class Logger
{   
private:
    static Logger* instancePtr;

    std::mutex m_mtx;

    std::string getTimeStamp();
    
    std::ofstream logFile;

    bool bLogFileOpened = false;

    Logger();
    ~Logger();
    // Prevent copy constructor 
    Logger(const Logger& obj) = delete;
    // Prevent copy assignment
    Logger& operator=(const Logger&) = delete;

public: 
    
    static Logger* getInstance();

    void setLogFile(const std::string& path);

    int log(const std::string& level, const std::string& message);

    int info(const std::string message);

    int debug(const std::string message);

    int error(const std::string message);

};