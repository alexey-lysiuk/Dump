cmake_minimum_required(VERSION 2.6)

project(Doom.II.RPG)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(PhysFS REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${PHYSFS_INCLUDE_DIR} src)
set(SOURCE_FILES src/main.cpp)

if (APPLE AND "${SDL2_LIBRARY}" MATCHES ".*\\.a$" )
	# Link with additional libraries/frameworks on macOS if SDL2 static library is used 
	set(CMAKE_EXE_LINKER_FLAGS "-liconv -framework AudioToolbox -framework Carbon -framework Cocoa -framework CoreAudio -framework CoreVideo -framework ForceFeedback -framework IOKit")
endif()

add_executable(Doom.II.RPG WIN32 MACOSX_BUNDLE ${SOURCE_FILES})
target_link_libraries(Doom.II.RPG ${SDL2_LIBRARY} ${PHYSFS_LIBRARY})
