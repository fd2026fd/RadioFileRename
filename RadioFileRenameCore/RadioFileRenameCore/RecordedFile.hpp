#pragma once
#include <filesystem>
#include <string>
#include <ctime>
#include "Config.hpp"

class RecordedFile {
public:
    std::filesystem::path path;

    RecordedFile(const std::filesystem::path& p)
        : path(p)
    {}

private:
    // 数字だけを抽出（unsigned char を使って安全に）
    static std::string extractDigits(const std::string& s) {
        std::string out;
        for (unsigned char c : s) {   // ★ここが重要
            if (isdigit(c)) {         // ★負の値でも安全
                out += c;
            }
        }
        return out;
    }

public:
    tm extractDate(const Config& config) const {
        tm t{};
        std::string full = path.filename().string();

        // ファイル名から数字だけ抽出
        std::string digits = extractDigits(full);

        // searchKeyword を後ろから探す
        auto pos = digits.rfind(config.searchKeyword);
        if (pos == std::string::npos) {
            return t;
        }

        // 14桁（YYYYMMDDhhmmss）があるか確認
        if (pos + 14 > digits.size()) {
            return t;
        }

        // YYYYMMDDhhmmss
        std::string datetime = digits.substr(pos, 14);

        int year = stoi(datetime.substr(0, 4));
        int month = stoi(datetime.substr(4, 2));
        int day = stoi(datetime.substr(6, 2));

        t.tm_year = year - 1900;
        t.tm_mon = month - 1;
        t.tm_mday = day;
        t.tm_hour = 0;
        t.tm_min = 0;
        t.tm_sec = 0;
        t.tm_isdst = -1;

        mktime(&t);
        return t;
    }
};
