cmake_minimum_required(VERSION 3.10)
project(Card_Game_66)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Detect platform name ---
if(NOT DEFINED PLATFORM_NAME)
    if(WIN32)
        set(PLATFORM_NAME "Windows")
    elseif(UNIX)
        set(PLATFORM_NAME "Linux")
    else()
        set(PLATFORM_NAME "Unknown")
    endif()
endif()

# --- Read version from Version.txt ---
file(READ "${CMAKE_SOURCE_DIR}/Version.txt" VERSION_STRING)
string(STRIP "${VERSION_STRING}" VERSION_STRING)
set(EXECUTABLE_NAME "Card_Game_66-${VERSION_STRING}-${PLATFORM_NAME}")

# --- Include paths ---
include_directories(include external/tinyxml2)

# --- Linux: use pkg-config to find SDL2 ---
if(PLATFORM_NAME STREQUAL "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
    link_libraries(${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
endif()

# --- Add Executables ---
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
    external/tinyxml2/tinyxml2.cpp
)

add_executable(Card_Viewer CardViewer.cpp)

# --- Platform-specific linking ---
if(PLATFORM_NAME STREQUAL "Windows")
    target_link_libraries(${EXECUTABLE_NAME} mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)
    target_link_libraries(Card_Viewer mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)

    # DLL copy logic: adjust to actual external structure
    get_filename_component(SOURCE_DIR "${CMAKE_SOURCE_DIR}" ABSOLUTE)
    set(SDL2_DLL_DIR         "${SOURCE_DIR}/external/SDL2-devel-2.32.8-mingw/SDL2-2.32.8/x86_64-w64-mingw32/bin")
    set(SDL2_IMAGE_DLL_DIR   "${SOURCE_DIR}/external/SDL2_image-devel-2.8.8-mingw/SDL2_image-2.8.8/x86_64-w64-mingw32/bin")
    set(SDL2_TTF_DLL_DIR     "${SOURCE_DIR}/external/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32/bin")

    foreach(TARGET_NAME IN ITEMS ${EXECUTABLE_NAME} Card_Viewer)
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL2_DLL_DIR}/SDL2.dll
                ${SDL2_IMAGE_DLL_DIR}/SDL2_image.dll
                ${SDL2_TTF_DLL_DIR}/SDL2_ttf.dll
                $<TARGET_FILE_DIR:${TARGET_NAME}>
        )
    endforeach()
else()  # Linux
    target_link_libraries(${EXECUTABLE_NAME} SDL2 SDL2_image SDL2_ttf)
    target_link_libraries(Card_Viewer SDL2 SDL2_image SDL2_ttf)
endif()

# --- Compiler warnings ---
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# --- Install (optional) ---
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
