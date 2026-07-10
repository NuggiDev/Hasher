#pragma once

#include "../hasher.h"
#include <string>
#include <vector>

class Formatter {
public:
    static std::string format_plain(const std::vector<HashResult>& results);
    static std::string format_json(const std::vector<HashResult>& results);
    static std::string format_sri(const HashResult& result);
};
