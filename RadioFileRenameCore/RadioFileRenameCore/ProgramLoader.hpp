#pragma once
#include <vector>
#include "RadioInfo.hpp"
#include "RadioProgram.hpp"

class ProgramLoader {
public:
    static std::vector<RadioProgram> loadFromRadioInfo(
        const RadioInfo* list, size_t count)
    {
        std::vector<RadioProgram> result;
        result.reserve(count);

        for (size_t i = 0; i < count; i++) {
            const auto& r = list[i];
            result.emplace_back(
                r.station_program,
                r.sun, r.mon, r.tue,
                r.wed, r.thu, r.fri, r.sat
            );
        }
        return result;
    }
};
