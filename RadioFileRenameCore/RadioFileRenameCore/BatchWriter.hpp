#pragma once
#include <fstream>
#include <string>

class BatchWriter {
    std::ofstream out;

public:
    BatchWriter(const std::string& path)
        : out(path)
    {}

    void write(const std::string& line) {
        out << line << "\n";
    }

    std::ofstream& stream() {
        return out;
    }
};
