cmake_minimum_required(VERSION 3.10)

project(serialport LANGUAGES C)

if(APPLE)
	set(PLATFORM_SOURCES macosx.c)
	set(PLATFORM_LINKER_FLAGS "-framework CoreFoundation" "-framework IOKit")
elseif(BSD)
	set(PLATFORM_SOURCES freebsd.c)
elseif(LINUX)
	set(PLATFORM_SOURCES linux.c)
else()
	set(PLATFORM_SOURCES windows.c)
endif()

include_directories("${CMAKE_SOURCE_DIR}")

add_library(serialport STATIC serialport.c libserialport.h timing.c ${PLATFORM_SOURCES})
target_compile_definitions(serialport PRIVATE LIBSERIALPORT_ATBUILD)

add_executable(list_ports list_ports.c)
target_link_libraries(list_ports PRIVATE serialport ${PLATFORM_LINKER_FLAGS})
