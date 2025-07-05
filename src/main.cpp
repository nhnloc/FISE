#include "Logger.h"
#include "FileScanner.h"
#include "Indexer.h"
#include "SearchEngine.h"
#include <chrono>
#include <sstream>
#include "cxxopts.hpp"


std::filesystem::path strLogDir = "log";


int main(int argc, char* argv[])
{
    cxxopts::Options options("FISE", "Fast indexing search engine");

    options.add_options()
        ("s,scan", "Scan directory", cxxopts::value<std::string>())
        ("q,search", "Search keyword", cxxopts::value<std::string>())
        ("h,help", "Print usage");

    cxxopts::ParseResult result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help();
        return 0;
    }

    std::filesystem::path strFileName = "log.txt";
    std::filesystem::path strLogFile = strLogDir / strFileName;
    Logger::getInstance().setLogFile(strLogFile);
    Logger::getInstance().info("Starting...");

    // std::vector<FileInfo> results;
    std::mutex resultMutex;
    Indexer indexer; 
    

    // auto emit = [&](FileInfo fi){
    //     std::lock_guard<std::mutex> lock(resultMutex);
    //     Logger::getInstance().info("Scanned: " + fi.strFileName + " (" + std::to_string(fi.uldFileSize) + " bytes)");        
    // };

    ThreadPool tp = ThreadPool(4);
    Indexer idx; 
    SearchEngine se = SearchEngine(idx);
    FileScanner fs = FileScanner(&tp, &idx);
    
    if (result.count("scan"))
    {
        std::string path = result["scan"].as<std::string>();
        fs.scanDir("./test");
        tp.waitForTask();
        indexer.printIndex();
    }

    if (result.count("search"))
    {
        fs.scanDir("test");
        tp.waitForTask();
        indexer.printIndex();
        std::string kw = result["search"].as<std::string>();
        auto results = se.search(kw);
        
        for (auto const& fi : results)
        {
            Logger::getInstance().info(fi.first.strFilePath + " | " + std::to_string(fi.first.uldFileSize) + " bytes");
            // std::cout << fi.first.strFilePath << "| " << fi.first.uldFileSize << "bytes\n";
        }
    }

    // fs.scanDir("./test");
    // std::vector<std::pair<FileInfo, int>> results = se.search("file");
    // for (const auto& result : results)
    // {
    //     std::cout << result.first.strFilePath << "   " << result.second << std::endl;
    // }
    // idx.printIndex();

    return 0;
}