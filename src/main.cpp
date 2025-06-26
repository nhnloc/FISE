#include "Logger.h"
#include "FileScanner.h"
#include "Indexer.h"
#include <chrono>
#include <sstream>


std::filesystem::path strLogDir = "log";


int main()
{
    std::filesystem::path strFileName = "log.txt";
    std::filesystem::path strLogFile = strLogDir / strFileName;
    Logger::getInstance().setLogFile(strLogFile);
    Logger::getInstance().info("Starting...");

    std::vector<FileInfo> results;
    std::mutex resultMutex;
    Indexer indexer; 
    

    auto emit = [&](FileInfo fi){
        std::lock_guard<std::mutex> lock(resultMutex);
        Logger::getInstance().info("Scanned: " + fi.strFileName + " (" + std::to_string(fi.uldFileSize) + " bytes)");        
    };

    ThreadPool tp = ThreadPool(4);
    Indexer idx; 
    FileScanner fs = FileScanner(&tp, &idx);

    fs.scanDir("./test");
    idx.printIndex();
    std::cout << "Total file scanned: " << results.size() << std::endl;
    return 0;
}