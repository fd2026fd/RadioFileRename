#pragma once
#include "FileAction.hpp"
#include "RecordedFile.hpp"
#include "FileNameFormatter.hpp"
#include "Config.hpp"
#include <filesystem>

class RenameAction : public FileAction {
    RecordedFile file;
    std::filesystem::path dstDir;
    const Config& config;

public:
    RenameAction(const RecordedFile& f,
        const std::filesystem::path& d,
        const Config& c)
        : file(f), dstDir(d), config(c) {}

    void writeBat(std::ofstream& out) override {
        tm date = file.extractDate(config);

        std::string newName =
            FileNameFormatter::format(file.path, date, config);

        out << "copy \"" << file.path.string() << "\" \""
            << (dstDir / newName).string() << "\"\n";

        out << "del \"" << file.path.string() << "\"\n";
    }
};
