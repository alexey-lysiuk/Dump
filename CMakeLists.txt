cmake_minimum_required(VERSION 2.6)

project(Doom.II.RPG)

include_directories(src)
set(SOURCE_FILES src/main.cpp)

add_executable(Doom.II.RPG WIN32 MACOSX_BUNDLE ${SOURCE_FILES})
