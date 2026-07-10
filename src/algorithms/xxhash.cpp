#include "../hasher.h"
#include "xxhash.h"
#include <sstream>

std::string Hasher::compute_xxhash64(const std::string& filepath) {
    std::string data = read_file_binary(filepath);
    XXH64_hash_t hash = XXH64(data.c_str(), data.length(), 0);
    
    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}
