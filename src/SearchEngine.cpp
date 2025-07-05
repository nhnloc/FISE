#include "SearchEngine.h"
#include <cmath>

SearchEngine::SearchEngine(Indexer &indexer) : m_indexer(indexer) {}

SearchEngine::~SearchEngine(){}

int SearchEngine::rank(const FileInfo& fi, const std::string& keyword) const
{
    int score = 0;
    if (fi.strFileName.find(keyword) != std::string::npos)
    {
        score += 50;
    }
    auto now = std::time(nullptr);
    double secondsDiff = std::difftime(now, fi.tLastModified);
    // int monthsAgo = static_cast<int>(secondsDiff / (60*60*24*30));
    double decay = std::exp(-secondsDiff / (60*60*24));
    // int recencyBonus = std::max(0, 12-monthsAgo);
    int recencyBonus = static_cast<int>(decay * 20);
    score += recencyBonus;
    return score;
}

std::vector<std::pair<FileInfo, int>> SearchEngine::search(const std::string &keyword) const
{
    std::vector<std::pair<FileInfo, int>> results;

    auto files = m_indexer.getFilesForKeyword(keyword);
    for (const auto& file : files)
    {
        int score = rank(file, keyword);
        results.emplace_back(file, score);
    }
    // Sorting the file base on their ranking
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b){
        return a.second > b.second;
    });

    return results;
}
