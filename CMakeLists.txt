cmake_minimum_required(VERSION 3.15)
project(hasher VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenSSL REQUIRED)

# BLAKE3
include(FetchContent)
FetchContent_Declare(
    blake3
    GIT_REPOSITORY https://github.com/BLAKE3-team/BLAKE3.git
    GIT_TAG 1.5.0
)
FetchContent_MakeAvailable(blake3)

# xxHash
FetchContent_Declare(
    xxHash
    GIT_REPOSITORY https://github.com/Cyan4973/xxHash.git
    GIT_TAG v0.8.1
)
FetchContent_MakeAvailable(xxHash)

# Main executable
add_executable(hasher
    src/main.cpp
    src/hasher.cpp
    src/algorithms/sha.cpp
    src/algorithms/blake3.cpp
    src/algorithms/xxhash.cpp
    src/output/formatter.cpp
    
    # Directly compile the portable algorithm files
    ${CMAKE_BINARY_DIR}/_deps/blake3-src/c/blake3.c
    ${CMAKE_BINARY_DIR}/_deps/blake3-src/c/blake3_dispatch.c
    ${CMAKE_BINARY_DIR}/_deps/blake3-src/c/blake3_portable.c
    ${CMAKE_BINARY_DIR}/_deps/blake3-src/c/blake3_neon.c
    ${CMAKE_BINARY_DIR}/_deps/xxhash-src/xxhash.c
)

if(MSVC)
    target_compile_options(hasher PRIVATE /FIwindows.h)
endif()

target_include_directories(hasher PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/_deps/blake3-src/c
    ${CMAKE_BINARY_DIR}/_deps/xxhash-src
)

target_link_libraries(hasher PRIVATE
    OpenSSL::Crypto
)

# Install
install(TARGETS hasher DESTINATION bin)