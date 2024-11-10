cmake_minimum_required(VERSION 3.20)

project("VDFParser" CXX)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_CXX_STANDARD 20)

add_library(VDFParser
        VDFParser.hpp
        src/errors.hpp
        src/vdf.cpp
        src/vdf.hpp
        src/keyvalue.hpp
        src/peekable-stream.cpp
        src/peekable-stream.hpp
        src/keyvalue.cpp
        src/case-insensitive-map.hpp
        src/case-insensitive-map.cpp
)

target_include_directories(
        VDFParser PRIVATE
        "src"
)
