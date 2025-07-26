# Toolchain_Windows.cmake
set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Resolve absolute source path
get_filename_component(SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
set(SDL2_ROOT ${SOURCE_DIR}/external)

# Correct subfolders (note the SDL2 subfolders inside SDL2-devel)
set(SDL2_PATH        ${SDL2_ROOT}/SDL2-devel-2.32.8-mingw/SDL2-2.32.8/x86_64-w64-mingw32)
set(SDL2_IMAGE_PATH  ${SDL2_ROOT}/SDL2_image-devel-2.8.8-mingw/SDL2_image-2.8.8/x86_64-w64-mingw32)
set(SDL2_TTF_PATH    ${SDL2_ROOT}/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32)

# Add includes (note the /SDL2 suffix required for #include <SDL2/SDL.h>)
include_directories(
    ${SDL2_PATH}/include/SDL2
    ${SDL2_IMAGE_PATH}/include/SDL2
    ${SDL2_TTF_PATH}/include/SDL2
)

# Add link libraries
link_directories(
    ${SDL2_PATH}/lib
    ${SDL2_IMAGE_PATH}/lib
    ${SDL2_TTF_PATH}/lib
)

# Help CMake find libraries
set(CMAKE_FIND_ROOT_PATH ${SDL2_ROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
