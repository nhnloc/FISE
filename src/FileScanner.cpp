#include "FileScanner.h"

#include <filesystem>

FileScanner::FileScanner(ThreadPool *tp, std::function<void(FileInfo)> emit) : m_tp(tp), m_emit(emit){}

void FileScanner::scanDir(const std::string &root)
{
    std::filesystem::path filePath = root;
    if (std::filesystem::is_regular_file(filePath))
    {
        // std::cout << filePath.string() << std::endl;
        FileInfo fi = FileInfo::fromPath(filePath.string());
        // std::cout << fi.strFileName << " " << fi.uldFileSize << std::endl;
        m_emit(std::move(fi));
        return;
    }
    for (const std::filesystem::directory_entry& dirEntry : std::filesystem::directory_iterator(filePath))
    {
        // if (dirEntry.is_regular_file())
        // {
        //     FileInfo fi = FileInfo::fromPath(dirEntry.path().string());
        //     m_emit(std::move(fi));
        // }
        // else if (dirEntry.is_directory())
        // {
            m_tp->enqueue([=](){
                scanDir(dirEntry.path().string());
            });
        // }
        // std::cout << dirEntry.path() << std::endl;
        // This should be replaced by ThreadPool
        // scanDir(dirEntry.path().string());
        
    }
}