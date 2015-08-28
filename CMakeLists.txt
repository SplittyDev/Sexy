cmake_minimum_required(VERSION 3.3)
project(sexy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/scanner.h src/scanner.cpp src/token.cpp src/token.h src/tokentype.h src/tokenposition.h)
add_executable(sexy ${SOURCE_FILES})