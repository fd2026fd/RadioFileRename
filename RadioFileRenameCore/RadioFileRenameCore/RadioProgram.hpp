#pragma once
#include <string>

class RadioProgram {
public:
    std::string name;
    bool sun, mon, tue, wed, thu, fri, sat;

    RadioProgram(const std::string& n,
        bool su, bool mo, bool tu,
        bool we, bool th, bool fr, bool sa)
        : name(n),
        sun(su), mon(mo), tue(tu),
        wed(we), thu(th), fri(fr), sat(sa)
    {}

    bool isValidDay(int wday) const {
        switch (wday) {
        case 0: return sun;
        case 1: return mon;
        case 2: return tue;
        case 3: return wed;
        case 4: return thu;
        case 5: return fri;
        case 6: return sat;
        }
        return false;
    }
};
