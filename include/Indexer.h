#pragma once
#include <FileInfo.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include <regex>

class Indexer
{
private: 
    std::unordered_map<std::string, std::vector<FileInfo>> m_invertedIndex;
    std::mutex m_mutex;
    std::vector<std::string> tokenize(const std::string& fileName) const;
    std::regex m_regex;
    // Indexer(const Indexer& obj) = delete;
    // Indexer& operator=(const Indexer&) = delete;

public: 

    void addFile(const FileInfo& file);
    // std::vector<std::string> search(const std::string& keyword) const;
    void printIndex() const;

    std::vector<FileInfo> getFilesForKeyword(const std::string& keyword);
};