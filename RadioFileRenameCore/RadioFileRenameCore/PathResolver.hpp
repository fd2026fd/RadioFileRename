#pragma once
#include <filesystem>
#include <string>

class PathResolver {
    std::string base;
    std::string del;
    std::string rename;

public:
    PathResolver(const std::string& baseDir,
        const std::string& delDir,
        const std::string& renameDir)
        : base(baseDir), del(delDir), rename(renameDir)
    {}

    std::filesystem::path source(const std::string& programName) const {
        return std::filesystem::path(base + programName);
    }

    std::filesystem::path delDir(const std::string& programName) const {
        return std::filesystem::path(del + programName);
    }

    std::filesystem::path renameDir(const std::string& programName) const {
        return std::filesystem::path(rename + programName);
    }
};
