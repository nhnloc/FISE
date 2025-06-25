#include "FileInfo.h"
#include "Logger.h"
#include <cerrno>
#include <cstring>

using namespace std::chrono_literals;

template <typename TP>
std::time_t to_time_t (TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration> (tp - TP::clock::now() + system_clock::now());
    return system_clock::to_time_t(sctp);
}

FileInfo FileInfo::fromPath(const std::string &path)
{
    FileInfo fi;
    std::filesystem::path filePath = path;
    if (!std::filesystem::exists(filePath) || !std::filesystem::is_regular_file(filePath))
    {
        // std::cout << "Path not exists";
        Logger::getInstance().error("Invalid file " + path);
        return fi;
    }

    fi.strFilePath = filePath.string();
    fi.strFileName = std::filesystem::path(filePath).filename().string();
    fi.uldFileSize = std::filesystem::file_size(filePath);
    std::filesystem::file_time_type fTime = std::filesystem::last_write_time(filePath);
    
    fi.tLastModified = to_time_t(fTime);

    return fi;
}