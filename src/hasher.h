#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

enum class Algorithm {
    SHA1,
    SHA256,
    SHA512,
    BLAKE3,
    XXHASH64
};

struct HashResult {
    std::string filename;
    std::map<Algorithm, std::string> hashes;
    bool success = false;
    std::string error;
};

enum class OutputFormat {
    Plain,
    JSON,
    SRI
};

class Hasher {
public:
    Hasher();
    
    // Compute hashes for a file
    HashResult hash_file(const std::string& filepath, 
                        const std::vector<Algorithm>& algos);
    
    // Compute hashes for multiple files
    std::vector<HashResult> hash_files(const std::vector<std::string>& filepaths,
                                       const std::vector<Algorithm>& algos);
    
    // Compute hashes recursively for a directory
    std::vector<HashResult> hash_directory(const std::string& dirpath,
                                           const std::vector<Algorithm>& algos);
    
    // Verify hashes from a file (e.g., .sha256)
    bool verify_hashes(const std::string& hash_file_path);
    
    // Format results for output
    std::string format_results(const std::vector<HashResult>& results,
                              OutputFormat format);
    
    static std::string algorithm_name(Algorithm algo);
    static std::string algorithm_short(Algorithm algo);

private:
    std::string compute_sha1(const std::string& filepath);
    std::string compute_sha256(const std::string& filepath);
    std::string compute_sha512(const std::string& filepath);
    std::string compute_blake3(const std::string& filepath);
    std::string compute_xxhash64(const std::string& filepath);
    
    std::string read_file_binary(const std::string& filepath);
};