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

#Add the executable
add_executable(Card_Game_66 
    main.cpp 
    src/Card.cpp
    src/Game.cpp)

#More warnings
target_compile_options(Card_Game_66 PRIVATE -Wall -Wextra -Wpedantic)