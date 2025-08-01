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
        ${SDL2_PATH}/include/SDL2
        ${SDL2_IMAGE_PATH}/include/SDL2
        ${SDL2_TTF_PATH}/include/SDL2
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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

    # Native Windows build (MinGW static libs with .a extensions)
    set(SDL2_PATH        "${CMAKE_SOURCE_DIR}/external/SDL2-devel-2.32.8-mingw/SDL2-2.32.8/x86_64-w64-mingw32")
    set(SDL2_IMAGE_PATH  "${CMAKE_SOURCE_DIR}/external/SDL2_image-devel-2.8.8-mingw/SDL2_image-2.8.8/x86_64-w64-mingw32")
    set(SDL2_TTF_PATH    "${CMAKE_SOURCE_DIR}/external/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32")

    foreach(path ${SDL2_PATH} ${SDL2_IMAGE_PATH} ${SDL2_TTF_PATH})
        if(NOT EXISTS "${path}/lib")
            message(FATAL_ERROR "Missing SDL library directory: ${path}/lib")
        endif()
    endforeach()

    set(SDL2_INCLUDE_DIRS
        ${SDL2_PATH}/include/SDL2
        ${SDL2_IMAGE_PATH}/include/SDL2
        ${SDL2_TTF_PATH}/include/SDL2
    )
    set(SDL2_LIBRARY_DIRS
        ${SDL2_PATH}/lib
        ${SDL2_IMAGE_PATH}/lib
        ${SDL2_TTF_PATH}/lib
    )
    # Use full path to .a libs instead of -l flags or .lib files
    set(SDL2_LIBS
        "${SDL2_PATH}/lib/libSDL2.a"
        "${SDL2_PATH}/lib/libSDL2main.a"
        "${SDL2_IMAGE_PATH}/lib/libSDL2_image.a"
        "${SDL2_TTF_PATH}/lib/libSDL2_ttf.a"
        winmm
        rpcrt4
        kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32
        setupapi imm32 version
    )

else()
    message(FATAL_ERROR "Unsupported host/target platform combination.")
endif()

# Gather source files
file(GLOB GAME_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/external/tinyxml2/*.cpp"
    "${CMAKE_SOURCE_DIR}/main.cpp"
)

# Create the game executable
add_executable(${EXECUTABLE_NAME} ${GAME_SOURCES})

# Viewer (single file, so no need to glob)
add_executable(Card_Viewer CardViewer.cpp)

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

if(WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SDL2_DLL "${CMAKE_SOURCE_DIR}/external/SDL2-devel-2.32.8-mingw/SDL2-2.32.8/x86_64-w64-mingw32/bin/SDL2.dll")
    set(SDL2_IMAGE_DLL "${CMAKE_SOURCE_DIR}/external/SDL2_image-devel-2.8.8-mingw/SDL2_image-2.8.8/x86_64-w64-mingw32/bin/SDL2_image.dll")
    set(SDL2_TTF_DLL "${CMAKE_SOURCE_DIR}/external/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32/bin/SDL2_ttf.dll")

    add_custom_command(TARGET Card_Viewer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_DLL} $<TARGET_FILE_DIR:Card_Viewer>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_IMAGE_DLL} $<TARGET_FILE_DIR:Card_Viewer>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_TTF_DLL} $<TARGET_FILE_DIR:Card_Viewer>
        COMMENT "Copying SDL2 DLLs for Windows target"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/resources"
        COMMENT "Copying resources to build folder"
    )
endif()
