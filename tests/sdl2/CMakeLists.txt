# /Volumes/Storage/Work/zdoom-macos-deps/prefix/bin/cmake -S . -B build -DCMAKE_PREFIX_PATH=/Volumes/Storage/Work/zdoom-macos-deps/prefix
# /Volumes/Storage/Work/zdoom-macos-deps/prefix/bin/cmake --build build

cmake_minimum_required( VERSION 3.1.0 )

project(sdl_test)

include( CheckCXXSourceCompiles )

find_package( SDL2 REQUIRED CONFIG )
include_directories( "${SDL2_INCLUDE_DIRS}" )
set(CMAKE_REQUIRED_INCLUDES "${CMAKE_REQUIRED_INCLUDES}" "${SDL2_INCLUDE_DIRS}")

CHECK_CXX_SOURCE_COMPILES("#include <SDL_version.h>
#if SDL_VERSION_ATLEAST(2, 0, 6)
int main() {}
#endif" SDL2_MIN_VERSION1 )

message("SDL2_MIN_VERSION1 = ${SDL2_MIN_VERSION1}")

CHECK_CXX_SOURCE_COMPILES("#include <SDL_version.h>
#if SDL_VERSION_ATLEAST(2, 0, 15)
int main() {}
#endif" SDL2_MIN_VERSION2 )

message("SDL2_MIN_VERSION2 = ${SDL2_MIN_VERSION2}")

add_executable(bmp bmp.cpp)
target_link_libraries(bmp SDL2::SDL2)
