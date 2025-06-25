#pragma once

#include <string>
#include <FileInfo.h>
#include "ThreadPool.h"

class FileScanner
{
private:
    ThreadPool* m_tp;
    std::function<void(FileInfo)> m_emit;

public: 
    FileScanner(ThreadPool* tp, std::function<void(FileInfo)> emit);
    void scanDir(const std::string& root);
};