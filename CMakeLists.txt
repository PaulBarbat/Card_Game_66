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

# --- Common includes ---
include_directories(include external/tinyxml2)

# --- Linux configuration ---
if(PLATFORM_NAME STREQUAL "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
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

# --- Platform-specific configuration ---
if(PLATFORM_NAME STREQUAL "Windows")
    # Fallback: define SDL2 paths if not already defined (e.g. from toolchain)
    if(NOT DEFINED SDL2_PATH)
        set(SDL2_PATH "${CMAKE_SOURCE_DIR}/external/SDL2-devel-2.32.8-mingw/SDL2-2.32.8/x86_64-w64-mingw32")
        set(SDL2_IMAGE_PATH "${CMAKE_SOURCE_DIR}/external/SDL2_image-devel-2.8.8-mingw/SDL2_image-2.8.8/x86_64-w64-mingw32")
        set(SDL2_TTF_PATH "${CMAKE_SOURCE_DIR}/external/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32")
    endif()

    # Include and link directories (must be here, not in toolchain file)
    include_directories(
        ${SDL2_PATH}/include/SDL2
        ${SDL2_IMAGE_PATH}/include/SDL2
        ${SDL2_TTF_PATH}/include/SDL2
    )

    link_directories(
        ${SDL2_PATH}/lib
        ${SDL2_IMAGE_PATH}/lib
        ${SDL2_TTF_PATH}/lib
    )

    # Link libraries
    set(WINDOWS_SDL2_LIBS mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)

    target_include_directories(${EXECUTABLE_NAME} PRIVATE
        ${SDL2_PATH}/include/SDL2
        ${SDL2_IMAGE_PATH}/include/SDL2
        ${SDL2_TTF_PATH}/include/SDL2
    )
    target_include_directories(Card_Viewer PRIVATE
        ${SDL2_PATH}/include/SDL2
        ${SDL2_IMAGE_PATH}/include/SDL2
        ${SDL2_TTF_PATH}/include/SDL2
    )

    target_link_libraries(${EXECUTABLE_NAME} ${WINDOWS_SDL2_LIBS})
    target_link_libraries(Card_Viewer ${WINDOWS_SDL2_LIBS})

    # --- Only copy DLLs if building natively on Windows ---
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
        file(GLOB_RECURSE SDL2_DLLS
            "${CMAKE_SOURCE_DIR}/external/*/x86_64-w64-mingw32/bin/SDL2.dll"
            "${CMAKE_SOURCE_DIR}/external/*/x86_64-w64-mingw32/bin/SDL2_image.dll"
            "${CMAKE_SOURCE_DIR}/external/*/x86_64-w64-mingw32/bin/SDL2_ttf.dll"
        )

        if(NOT SDL2_DLLS)
            message(FATAL_ERROR "Could not find required SDL2 DLLs under external/.")
        endif()

        foreach(TARGET_NAME IN ITEMS ${EXECUTABLE_NAME} Card_Viewer)
            foreach(DLL_PATH IN LISTS SDL2_DLLS)
                add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "${DLL_PATH}"
                        $<TARGET_FILE_DIR:${TARGET_NAME}>
                )
            endforeach()
        endforeach()
    endif()

else()  # Linux
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

    target_link_libraries(${EXECUTABLE_NAME}
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
    )
    target_link_libraries(Card_Viewer
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
    )
endif()

# --- Compiler warnings ---
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# --- Install (optional) ---
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
