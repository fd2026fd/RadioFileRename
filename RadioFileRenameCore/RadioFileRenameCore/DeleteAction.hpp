#pragma once
#include "FileAction.hpp"
#include <filesystem>

class DeleteAction : public FileAction {
    std::filesystem::path src;
    std::filesystem::path dstDir;

public:
    DeleteAction(const std::filesystem::path& s,
        const std::filesystem::path& d)
        : src(s), dstDir(d) {}

    void writeBat(std::ofstream& out) override {
        out << "copy \"" << src.string() << "\" \""
            << (dstDir / src.filename()).string() << "\"\n";

        out << "del \"" << src.string() << "\"\n";
    }
};
