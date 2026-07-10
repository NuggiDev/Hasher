cmake_minimum_required(VERSION 3.15)

if(WIN32)
    # Read target arch from the env var set by vcvarsall.bat
    set(_ARCH "$ENV{VSCMD_ARG_TGT_ARCH}")
    if(NOT _ARCH)
        string(TOLOWER "$ENV{PROCESSOR_ARCHITECTURE}" _ARCH)
    endif()

    file(GLOB _MSVC_DIRS
        "C:/Program Files (x86)/Microsoft Visual Studio/*/BuildTools/VC/Tools/MSVC/*")
    list(SORT _MSVC_DIRS ORDER DESCENDING)
    if(_MSVC_DIRS)
        list(GET _MSVC_DIRS 0 _MSVC_DIR)
    endif()

    
    file(GLOB _SDK_DIRS "C:/Program Files (x86)/Windows Kits/10/Lib/*")
    list(SORT _SDK_DIRS ORDER DESCENDING)
    if(_SDK_DIRS)
        list(GET _SDK_DIRS 0 _LATEST_SDK)
    endif()

    if(_MSVC_DIR AND _LATEST_SDK AND _ARCH)
        set(ENV{LIB}
            "$ENV{LIB};${_MSVC_DIR}/lib/${_ARCH};${_LATEST_SDK}/ucrt/${_ARCH};${_LATEST_SDK}/um/${_ARCH}")
        message(STATUS "Auto-fixed LIB for ${_ARCH}: ${_MSVC_DIR}/lib/${_ARCH}")
    endif()
endif()

project(hasher VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32 AND _MSVC_DIR AND _LATEST_SDK AND _ARCH)
    link_directories(
        "${_MSVC_DIR}/lib/${_ARCH}"
        "${_LATEST_SDK}/ucrt/${_ARCH}"
        "${_LATEST_SDK}/um/${_ARCH}"
    )
endif()

find_package(OpenSSL REQUIRED)

include(FetchContent)
FetchContent_Declare(
    blake3
    GIT_REPOSITORY https://github.com/BLAKE3-team/BLAKE3.git
    GIT_TAG 1.5.0
)
FetchContent_MakeAvailable(blake3)

FetchContent_Declare(
    xxHash
    GIT_REPOSITORY https://github.com/Cyan4973/xxHash.git
    GIT_TAG v0.8.1
)
FetchContent_MakeAvailable(xxHash)

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

install(TARGETS hasher DESTINATION bin)