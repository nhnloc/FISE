#include "FileScanner.h"

#include <filesystem>

// FileScanner::FileScanner(ThreadPool *tp, std::function<void(FileInfo)> emit) : m_tp(tp), m_emit(emit){}
FileScanner::FileScanner(ThreadPool *tp, Indexer* indexer) : m_tp(tp), m_indexer(indexer){}
void FileScanner::scanDir(const std::string &root)
{
    std::filesystem::path filePath = root;
    if (std::filesystem::is_regular_file(filePath))
    {
        // std::cout << filePath.string() << std::endl;
        FileInfo fi = FileInfo::fromPath(filePath.string());
        // std::cout << fi.strFileName << " " << fi.uldFileSize << std::endl;
        // m_emit(std::move(fi));
        m_tp->enqueue([this, fi](){
            m_indexer->addFile(std::move(fi));
        });
        return;
    }
    for (const std::filesystem::directory_entry& dirEntry : std::filesystem::directory_iterator(filePath))
    {
        m_tp->enqueue([=](){
            scanDir(dirEntry.path().string());
        });
    }
}