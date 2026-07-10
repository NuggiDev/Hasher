#include "hasher.h"
#include "output/formatter.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file1> [file2...]\n";
        return 1;
    }

    std::vector<std::string> files;
    for (int i = 1; i < argc; ++i) {
        files.push_back(argv[i]);
    }

    Hasher hasher;
    
    std::vector<Algorithm> algos = {
        Algorithm::SHA1,
        Algorithm::SHA256,
        Algorithm::SHA512,
        Algorithm::BLAKE3,
        Algorithm::XXHASH64
    };
    
    auto results = hasher.hash_files(files, algos);
    std::cout << hasher.format_results(results, OutputFormat::Plain);

    return 0;
}
