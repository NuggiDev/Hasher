#include "../hasher.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <openssl/evp.h>

extern std::string bytes_to_hex(const unsigned char* bytes, size_t length);

std::string Hasher::compute_sha1(const std::string& filepath) {
    std::string data = read_file_binary(filepath);
    unsigned char hash[SHA_DIGEST_LENGTH];
    
    SHA1(reinterpret_cast<const unsigned char*>(data.c_str()), 
         data.length(), hash);
    
    return bytes_to_hex(hash, SHA_DIGEST_LENGTH);
}

std::string Hasher::compute_sha256(const std::string& filepath) {
    std::string data = read_file_binary(filepath);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), 
           data.length(), hash);
    
    return bytes_to_hex(hash, SHA256_DIGEST_LENGTH);
}

std::string Hasher::compute_sha512(const std::string& filepath) {
    std::string data = read_file_binary(filepath);
    unsigned char hash[SHA512_DIGEST_LENGTH];
    
    SHA512(reinterpret_cast<const unsigned char*>(data.c_str()), 
           data.length(), hash);
    
    return bytes_to_hex(hash, SHA512_DIGEST_LENGTH);
}
