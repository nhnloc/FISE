#include "Logger.h"
#include "FileScanner.h"
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

    auto emit = [&](FileInfo fi){
        std::lock_guard<std::mutex> lock(resultMutex);
        Logger::getInstance().info("Scanned: " + fi.strFileName + " (" + std::to_string(fi.uldFileSize) + " bytes)");
        results.push_back(std::move(fi));
    };

    ThreadPool tp = ThreadPool(4);
    FileScanner fs = FileScanner(&tp, emit);

    fs.scanDir("./test");
    std::cout << "Total file scanned: " << results.size() << std::endl;
    return 0;
}      