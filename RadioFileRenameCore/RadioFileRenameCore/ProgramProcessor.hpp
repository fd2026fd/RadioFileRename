#pragma once
#include <filesystem>
#include <memory>
#include "RadioProgram.hpp"
#include "RecordedFile.hpp"
#include "FileAction.hpp"
#include "RenameAction.hpp"
#include "DeleteAction.hpp"
#include "BatchWriter.hpp"
#include "PathResolver.hpp"
#include "Config.hpp"

namespace fs = std::filesystem;

class ProgramProcessor {
    RadioProgram program;

public:
    ProgramProcessor(const RadioProgram& p)
        : program(p)
    {}

    void process(BatchWriter& writer,
        const PathResolver& resolver,
        const Config& config)
    {
        auto srcDir = resolver.source(program.name);
        auto delDir = resolver.delDir(program.name);
        auto renDir = resolver.renameDir(program.name);

        writer.write("mkdir \"" + delDir.string() + "\"");
        writer.write("mkdir \"" + renDir.string() + "\"");

        if (!fs::is_directory(srcDir)) return;

        for (auto& entry : fs::directory_iterator(srcDir)) {
            RecordedFile rec(entry.path());
            tm t = rec.extractDate(config);

            std::unique_ptr<FileAction> action;

            if (program.isValidDay(t.tm_wday)) {
                action = std::make_unique<RenameAction>(rec, renDir, config);
            }
            else {
                action = std::make_unique<DeleteAction>(rec.path, delDir);
            }

            action->writeBat(writer.stream());
        }
    }
};
