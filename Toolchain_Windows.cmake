# Toolchain_Windows.cmake
set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# SDL2 (relative to source dir)
get_filename_component(SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
set(SDL2_ROOT ${SOURCE_DIR}/external)

include_directories(
    ${SDL2_ROOT}/SDL2/x86_64-w64-mingw32/include
    ${SDL2_ROOT}/SDL2_image/x86_64-w64-mingw32/include
    ${SDL2_ROOT}/SDL2_ttf/x86_64-w64-mingw32/include
)

link_directories(
    ${SDL2_ROOT}/SDL2/x86_64-w64-mingw32/lib
    ${SDL2_ROOT}/SDL2_image/x86_64-w64-mingw32/lib
    ${SDL2_ROOT}/SDL2_ttf/x86_64-w64-mingw32/lib
)

set(CMAKE_FIND_ROOT_PATH ${SDL2_ROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
