cmake_minimum_required(VERSION 3.10)
project(Card_Game_66)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Read version number safely ---
if(EXISTS "${CMAKE_SOURCE_DIR}/Version.txt")
    file(READ "${CMAKE_SOURCE_DIR}/Version.txt" VERSION_STRING)
    string(STRIP "${VERSION_STRING}" VERSION_STRING)
else()
    set(VERSION_STRING "0.0.0")
endif()

set(EXECUTABLE_NAME "Card_Game_66-${VERSION_STRING}")

# --- Common includes ---
set(PROJECT_COMMON_INCLUDES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/tinyxml2
)

# --- Platform detection ---
message(STATUS "Host platform: ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "Target platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Cross compiling: ${CMAKE_CROSSCOMPILING}")

set(SDL2_INCLUDE_DIRS "")
set(SDL2_LIBRARY_DIRS "")
set(SDL2_LIBS "")

# --- Platform-specific SDL2 config ---
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Native Linux build
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

    set(SDL2_INCLUDE_DIRS
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
    )
    set(SDL2_LIBS
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
    )

elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Cross-compiling on Linux for Windows
    set(SDL2_PATH        "${CMAKE_SOURCE_DIR}/external/SDL2-devel-2.32.8-mingw/SDL2-2.32.8/x86_64-w64-mingw32")
    set(SDL2_IMAGE_PATH  "${CMAKE_SOURCE_DIR}/external/SDL2_image-devel-2.8.8-mingw/SDL2_image-2.8.8/x86_64-w64-mingw32")
    set(SDL2_TTF_PATH    "${CMAKE_SOURCE_DIR}/external/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32")

    foreach(path ${SDL2_PATH} ${SDL2_IMAGE_PATH} ${SDL2_TTF_PATH})
        if(NOT EXISTS "${path}/lib")
            message(FATAL_ERROR "Missing SDL library directory: ${path}/lib")
        endif()
    endforeach()

    set(SDL2_INCLUDE_DIRS
        ${SDL2_PATH}/include
        ${SDL2_IMAGE_PATH}/include
        ${SDL2_TTF_PATH}/include
    )
    set(SDL2_LIBRARY_DIRS
        ${SDL2_PATH}/lib
        ${SDL2_IMAGE_PATH}/lib
        ${SDL2_TTF_PATH}/lib
    )
    set(SDL2_LIBS
        -lmingw32
        -lSDL2main
        -lSDL2
        -lSDL2_image
        -lSDL2_ttf
        -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32
        -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
    )

elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows" AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Native Windows build
    set(SDL2_PATH        "${CMAKE_SOURCE_DIR}/external/SDL2")
    set(SDL2_IMAGE_PATH  "${CMAKE_SOURCE_DIR}/external/SDL2_image")
    set(SDL2_TTF_PATH    "${CMAKE_SOURCE_DIR}/external/SDL2_ttf")

    foreach(path ${SDL2_PATH} ${SDL2_IMAGE_PATH} ${SDL2_TTF_PATH})
        if(NOT EXISTS "${path}/lib")
            message(FATAL_ERROR "Missing SDL library directory: ${path}/lib")
        endif()
    endforeach()

    set(SDL2_INCLUDE_DIRS
        ${SDL2_PATH}/include
        ${SDL2_IMAGE_PATH}/include
        ${SDL2_TTF_PATH}/include
    )
    set(SDL2_LIBRARY_DIRS
        ${SDL2_PATH}/lib
        ${SDL2_IMAGE_PATH}/lib
        ${SDL2_TTF_PATH}/lib
    )
    set(SDL2_LIBS
        SDL2main
        SDL2
        SDL2_image
        SDL2_ttf
    )
else()
    message(FATAL_ERROR "Unsupported host/target platform combination.")
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

add_executable(Card_Viewer
    CardViewer.cpp
)

# --- Apply include paths ---
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${PROJECT_COMMON_INCLUDES} ${SDL2_INCLUDE_DIRS})
target_include_directories(Card_Viewer PRIVATE ${PROJECT_COMMON_INCLUDES} ${SDL2_INCLUDE_DIRS})

# --- Apply library paths and linking ---
if(SDL2_LIBRARY_DIRS)
    target_link_directories(${EXECUTABLE_NAME} PRIVATE ${SDL2_LIBRARY_DIRS})
    target_link_directories(Card_Viewer PRIVATE ${SDL2_LIBRARY_DIRS})
endif()

target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${SDL2_LIBS})
target_link_libraries(Card_Viewer PRIVATE ${SDL2_LIBS})

# --- Compiler warnings ---
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# --- Install target (optional) ---
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
