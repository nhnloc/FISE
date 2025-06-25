#pragma once

#include <string>
#include <filesystem>

#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>

class FileInfo
{
public:
    std::string strFilePath;
    std::string strFileName;
    std::size_t uldFileSize;
    // std::filesystem::file_time_type tLastModified;
    std::time_t tLastModified;

    static FileInfo fromPath(const std::string& path);
};