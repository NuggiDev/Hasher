#include "hasher.h"
#include "output/formatter.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <iomanip>

namespace fs = std::filesystem;

Hasher::Hasher() {}

std::string Hasher::read_file_binary(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string bytes_to_hex(const unsigned char* bytes, size_t length) {
    std::stringstream ss;
    for (size_t i = 0; i < length; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)bytes[i];
    }
    return ss.str();
}



HashResult Hasher::hash_file(const std::string& filepath, 
                            const std::vector<Algorithm>& algos) {
    HashResult result;
    result.filename = filepath;
    
    if (!fs::exists(filepath)) {
        result.success = false;
        result.error = "File not found: " + filepath;
        return result;
    }
    
    try {
        for (const auto& algo : algos) {
            switch (algo) {
                case Algorithm::SHA1:
                    result.hashes[algo] = compute_sha1(filepath);
                    break;
                case Algorithm::SHA256:
                    result.hashes[algo] = compute_sha256(filepath);
                    break;
                case Algorithm::SHA512:
                    result.hashes[algo] = compute_sha512(filepath);
                    break;
                case Algorithm::BLAKE3:
                    result.hashes[algo] = compute_blake3(filepath);
                    break;
                case Algorithm::XXHASH64:
                    result.hashes[algo] = compute_xxhash64(filepath);
                    break;
            }
        }
        result.success = true;
    } catch (const std::exception& e) {
        result.success = false;
        result.error = e.what();
    }
    
    return result;
}

std::vector<HashResult> Hasher::hash_files(const std::vector<std::string>& filepaths,
                                           const std::vector<Algorithm>& algos) {
    std::vector<HashResult> results;
    for (const auto& filepath : filepaths) {
        results.push_back(hash_file(filepath, algos));
    }
    return results;
}

std::vector<HashResult> Hasher::hash_directory(const std::string& dirpath,
                                               const std::vector<Algorithm>& algos) {
    std::vector<HashResult> results;
    
    if (!fs::is_directory(dirpath)) {
        HashResult result;
        result.filename = dirpath;
        result.success = false;
        result.error = "Not a directory: " + dirpath;
        results.push_back(result);
        return results;
    }
    
    for (const auto& entry : fs::recursive_directory_iterator(dirpath)) {
        if (entry.is_regular_file()) {
            results.push_back(hash_file(entry.path().string(), algos));
        }
    }
    
    return results;
}

bool Hasher::verify_hashes(const std::string& hash_file_path) {
    if (!fs::exists(hash_file_path)) {
        std::cerr << "Hash file not found: " << hash_file_path << std::endl;
        return false;
    }
    
    std::ifstream hashfile(hash_file_path);
    std::string line;
    bool all_valid = true;
    
    while (std::getline(hashfile, line)) {
        // Parse format: "hash filename"
        std::istringstream iss(line);
        std::string expected_hash, filename;
        
        if (!(iss >> expected_hash >> filename)) continue;
        
        try {
            std::vector<Algorithm> algos = {Algorithm::SHA256};
            HashResult result = hash_file(filename, algos);
            
            if (result.hashes[Algorithm::SHA256] == expected_hash) {
                std::cout << "✓ " << filename << std::endl;
            } else {
                std::cout << "✗ " << filename << " MISMATCH" << std::endl;
                all_valid = false;
            }
        } catch (const std::exception& e) {
            std::cout << "✗ " << filename << " ERROR: " << e.what() << std::endl;
            all_valid = false;
        }
    }
    
    return all_valid;
}

std::string Hasher::format_results(const std::vector<HashResult>& results,
                                  OutputFormat format) {
    switch (format) {
        case OutputFormat::Plain:
            return Formatter::format_plain(results);
        case OutputFormat::JSON:
            return Formatter::format_json(results);
        default:
            return Formatter::format_plain(results);
    }
}

std::string Hasher::algorithm_name(Algorithm algo) {
    switch (algo) {
        case Algorithm::SHA1: return "SHA1";
        case Algorithm::SHA256: return "SHA256";
        case Algorithm::SHA512: return "SHA512";
        case Algorithm::BLAKE3: return "BLAKE3";
        case Algorithm::XXHASH64: return "xxHash64";
        default: return "Unknown";
    }
}

std::string Hasher::algorithm_short(Algorithm algo) {
    switch (algo) {
        case Algorithm::SHA1: return "sha1";
        case Algorithm::SHA256: return "sha256";
        case Algorithm::SHA512: return "sha512";
        case Algorithm::BLAKE3: return "blake3";
        case Algorithm::XXHASH64: return "xxhash64";
        default: return "unknown";
    }
}
