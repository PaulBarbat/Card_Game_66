cmake_minimum_required(VERSION 3.10)
project(Card_Game_66)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)
include_directories(external/tinyxml2)

# Read version from Version.txt
file(READ "${CMAKE_SOURCE_DIR}/Version.txt" VERSION_STRING)
string(STRIP "${VERSION_STRING}" VERSION_STRING)

# Platform name passed from command line
if(NOT DEFINED PLATFORM_NAME)
    set(PLATFORM_NAME "unknown")
endif()

# Set executable name
if(WIN32)
    set(EXECUTABLE_NAME "Card_Game_66-${VERSION_STRING}-${PLATFORM_NAME}")
else()
    set(EXECUTABLE_NAME "Card_Game_66-${VERSION_STRING}-${PLATFORM_NAME}")
endif()

# Add the executable
add_executable(${EXECUTABLE_NAME}
    main.cpp
    src/CardFactory.cpp
    src/Deck.cpp
    src/Game.cpp
    src/Player.cpp
    src/StartState.cpp
    src/ShuffleAndDrawState.cpp
    src/PlayHandState.cpp
    CalculateHandPointsState.cpp
    GameOverState.cpp
    external/tinyxml2/tinyxml2.cpp)

# Compiler warnings
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# Install (optional)
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
