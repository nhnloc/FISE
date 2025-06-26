#include "Indexer.h"

std::vector<std::string> Indexer::tokenize(const std::string &fileName) const
{
    std::vector<std::string> result;

    std::string name = fileName.substr(0, fileName.find_last_of('.'));

    std::regex wordRegex("[A-Za-z0-9]+");
    auto wordBegin = std::sregex_iterator(name.begin(), name.end(), wordRegex);
    auto wordEnd = std::sregex_iterator();

    for (auto it = wordBegin; it != wordEnd; ++it)
    {
        result.push_back(it->str());
    }
    return result;
}

void Indexer::addFile(const FileInfo &file)
{
    std::vector<std::string> keywords = tokenize(file.strFileName);

    std::lock_guard<std::mutex> lock(m_mutex);
    for (const std::string& keyword : keywords)
    {
        m_invertedIndex[keyword].push_back(file.strFilePath);
    }
}

std::vector<std::string> Indexer::search(const std::string &keyword) const
{
    return std::vector<std::string>();
}

void Indexer::printIndex() const
{

    for (const std::pair<const std::string, std::vector<std::string>>& n : m_invertedIndex)
    {
        // printKeyValue(n.first, n.second);
        std::cout << "Keyword: " << n.first << std::endl;
        for (const std::string& path : n.second)
        {
            std::cout << "-------" << path << std::endl; 
        }
    }
    
}