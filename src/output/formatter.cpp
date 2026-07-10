#include "formatter.h"
#include <sstream>

std::string Formatter::format_plain(const std::vector<HashResult>& results) {
    std::stringstream ss;
    for (const auto& res : results) {
        if (!res.success) {
            ss << "Error (" << res.filename << "): " << res.error << "\n";
            continue;
        }
        for (const auto& pair : res.hashes) {
            ss << Hasher::algorithm_name(pair.first) << " (" << res.filename << ") = " << pair.second << "\n";
        }
    }
    return ss.str();
}

std::string Formatter::format_json(const std::vector<HashResult>& results) {
    std::stringstream ss;
    ss << "[\n";
    for (size_t i = 0; i < results.size(); ++i) {
        const auto& res = results[i];
        ss << "  {\n";
        ss << "    \"filename\": \"" << res.filename << "\",\n";
        if (res.success) {
            ss << "    \"success\": true,\n";
            ss << "    \"hashes\": {\n";
            size_t j = 0;
            for (const auto& pair : res.hashes) {
                ss << "      \"" << Hasher::algorithm_short(pair.first) << "\": \"" << pair.second << "\"";
                if (j < res.hashes.size() - 1) ss << ",";
                ss << "\n";
                j++;
            }
            ss << "    }\n";
        } else {
            ss << "    \"success\": false,\n";
            ss << "    \"error\": \"" << res.error << "\"\n";
        }
        ss << "  }";
        if (i < results.size() - 1) ss << ",";
        ss << "\n";
    }
    ss << "]\n";
    return ss.str();
}

std::string Formatter::format_sri(const HashResult& result) {
    // Stub for now
    return "";
}
