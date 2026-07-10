#include "../hasher.h"
#include "blake3.h"

extern std::string bytes_to_hex(const unsigned char* bytes, size_t length);

std::string Hasher::compute_blake3(const std::string& filepath) {
    std::string data = read_file_binary(filepath);
    uint8_t hash[BLAKE3_OUT_LEN];
    
    blake3_hasher hasher;
    blake3_hasher_init(&hasher);
    blake3_hasher_update(&hasher, 
                        reinterpret_cast<const uint8_t*>(data.c_str()),
                        data.length());
    blake3_hasher_finalize(&hasher, hash, BLAKE3_OUT_LEN);
    
    return bytes_to_hex(hash, BLAKE3_OUT_LEN);
}
