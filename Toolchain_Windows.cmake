# Toolchain_Windows.cmake

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Paths
get_filename_component(SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
set(SDL2_ROOT "${SOURCE_DIR}/external")

set(SDL2_PATH        "${SDL2_ROOT}/SDL2-devel-2.32.8-mingw/SDL2-2.32.8/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH  "${SDL2_ROOT}/SDL2_image-devel-2.8.8-mingw/SDL2_image-2.8.8/x86_64-w64-mingw32")
set(SDL2_TTF_PATH    "${SDL2_ROOT}/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32")

# Add include and lib directories
set(CMAKE_INCLUDE_PATH
    ${SDL2_PATH}/include
    ${SDL2_IMAGE_PATH}/include
    ${SDL2_TTF_PATH}/include
)

set(CMAKE_LIBRARY_PATH
    ${SDL2_PATH}/lib
    ${SDL2_IMAGE_PATH}/lib
    ${SDL2_TTF_PATH}/lib
)

set(CMAKE_FIND_ROOT_PATH ${SDL2_ROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
