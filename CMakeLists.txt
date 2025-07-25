cmake_minimum_required(VERSION 3.10)
project(Card_Game_66)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Determine platform name (Linux/Windows)
if(NOT DEFINED PLATFORM_NAME)
    if(WIN32)
        set(PLATFORM_NAME "Windows")
    elseif(UNIX)
        set(PLATFORM_NAME "Linux")
    else()
        set(PLATFORM_NAME "Unknown")
    endif()
endif()

# Read version from Version.txt
file(READ "${CMAKE_SOURCE_DIR}/Version.txt" VERSION_STRING)
string(STRIP "${VERSION_STRING}" VERSION_STRING)

# Executable name
set(EXECUTABLE_NAME "Card_Game_66-${VERSION_STRING}-${PLATFORM_NAME}")

# TinyXML include
include_directories(include external/tinyxml2)

# SDL2 includes for both Linux and Windows
find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
link_libraries(${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})


# Main game executable
add_executable(${EXECUTABLE_NAME}
    main.cpp
    src/CardFactory.cpp
    src/Deck.cpp
    src/Game.cpp
    src/Player.cpp
    src/StartState.cpp
    src/ShuffleAndDrawState.cpp
    src/PlayHandState.cpp
    src/CalculateHandPointsState.cpp
    src/GameOverState.cpp
    external/tinyxml2/tinyxml2.cpp)

# Viewer tool (optional)
add_executable(Card_Viewer CardViewer.cpp)

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} SDL2 SDL2_image SDL2_ttf)
target_link_libraries(Card_Viewer SDL2 SDL2_image SDL2_ttf)

# Compiler warnings
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# Install (optional)
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
