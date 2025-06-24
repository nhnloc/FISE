#include "Logger.h"

std::filesystem::path strLogDir = "log";

int main()
{
    std::filesystem::path strFileName = "log.txt";
    std::filesystem::path strLogFile = strLogDir / strFileName;
    Logger::getInstance()->setLogFile(strLogFile);
    Logger::getInstance()->info("Starting...");
    
    return 0;
}      