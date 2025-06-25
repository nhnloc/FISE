#include "Logger.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Logger::Logger(){}

Logger::~Logger()
{
    if (logFile.is_open())
        logFile.close();
}

Logger& Logger::getInstance()
{
    // Old way, not thread-safe

    // if (instancePtr == nullptr)
    // {
    //     instancePtr = new Logger();
    // }
    // return instancePtr;

    // Meyers Singleton --> best practice
    static Logger instance;
    return instance;

}

std::string Logger::getTimeStamp()
{
    std::ostringstream oss;
    std::time_t t = std::time(nullptr);
    
    std::tm tm = *std::localtime(&t);
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Logger::setLogFile(const std::string &path)
{
    // Lock guard is smart function used to lock and unlock mutex
    std::lock_guard<std::mutex> guard(m_mtx);
    logFile.open(path, std::ios::app);
    // Set a flag to indicate file is opened
    bLogFileOpened = true;
}

int Logger::log(const std::string &level, const std::string &message)
{
    std::lock_guard<std::mutex> guard(m_mtx);   
    std::string strLine = "[" + getTimeStamp() + "] [" + level + "] " + message;
    std::cout << strLine << std::endl;
    if (bLogFileOpened) 
        logFile << strLine << std::endl;
    return 0;
}

int Logger::info(const std::string message)
{
    log("INFO", message);
    return 0;
}

int Logger::debug(const std::string message)
{
    log("DEBUG", message);
    return 0;
}

int Logger::error(const std::string message)
{
    log("ERROR", message);
    return 0;
}
