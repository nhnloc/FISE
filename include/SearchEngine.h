#pragma once 
#include "Indexer.h"

class SearchEngine
{
private:
    Indexer& m_indexer;

    int rank(const FileInfo& fi, const std::string& keyword) const;

public: 
    SearchEngine(Indexer& indexer);
    ~SearchEngine();

    std::vector<std::pair<FileInfo, int>> search(const std::string& keyword) const;
};