cmake_minimum_required(VERSION 3.10)
project(Card_Game_66)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify Clang as the compiler
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

#include directories
include_directories(include)

#read version
file(READ "${CMAKE_SOURCE_DIR}/Version.txt" VERSION_STRING)
string(STRIP "${VERSION_STRING}" VERSION_STRING)

#set version in executable name
set(EXECUTABLE_NAME "Card_Game_66-${VERSION_STRING}")

#Add the executable
add_executable(${EXECUTABLE_NAME}
    main.cpp 
    src/Card.cpp
    src/Game.cpp)

#More warnings
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)