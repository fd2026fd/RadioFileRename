#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include "Config.hpp"

class FileNameFormatter {
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
    static std::string format(const std::filesystem::path& original,
        const tm& date,
        const Config& config)
    {
        std::string full = original.filename().string();

        // ファイル名から数字だけ抽出
        std::string digits = extractDigits(full);

        // searchKeyword を後ろから探す
        auto pos = digits.rfind(config.searchKeyword);
        if (pos == std::string::npos) {
            return full;
        }

        // 14桁（YYYYMMDDhhmmss）があるか確認
        if (pos + 14 > digits.size()) {
            return full;
        }

        // YYYYMMDDhhmmss
        std::string datetime = digits.substr(pos, 14);

        // hhmm を取り出す
        std::string hhmm = datetime.substr(8, 4);

        // 新しいファイル名を作成
        std::ostringstream ss;
        ss << (date.tm_year + 1900)
            << std::setw(2) << std::setfill('0') << (date.tm_mon + 1)
            << std::setw(2) << std::setfill('0') << date.tm_mday
            << hhmm
            << "_" << full;

        return ss.str();
    }
};
