#pragma once

#include <string>
#include <FileInfo.h>
#include "ThreadPool.h"
#include "Indexer.h"

class FileScanner
{
private:
    ThreadPool* m_tp;
    Indexer* m_indexer;
    std::function<void(FileInfo)> m_emit;


public: 
    // FileScanner(ThreadPool* tp, std::function<void(FileInfo)> emit);
    FileScanner(ThreadPool* tp, Indexer *indexer);
    void scanDir(const std::string& root);
};