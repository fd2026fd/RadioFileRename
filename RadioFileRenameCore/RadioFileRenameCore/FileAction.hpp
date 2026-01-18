#pragma once
#include <fstream>

class FileAction {
public:
    virtual ~FileAction() = default;
    virtual void writeBat(std::ofstream& out) = 0;
};
