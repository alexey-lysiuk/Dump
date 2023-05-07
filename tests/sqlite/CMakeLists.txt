cmake_minimum_required(VERSION 3.1.0)

project(sqlite)

add_library(sqlite3 STATIC
	sqlite3.c
	sqlite3.h
)

set(SQLITE_TESTS
	kvtest
	speedtest1
)

foreach(SQLITE_TEST IN LISTS SQLITE_TESTS)
	add_executable(${SQLITE_TEST} ${SQLITE_TEST}.c)
	set_target_properties(${SQLITE_TEST} PROPERTIES 
		LINK_LIBRARIES sqlite3
	)
endforeach()
