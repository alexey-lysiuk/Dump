cmake_minimum_required( VERSION 3.1.0 )

project(unqlite_tests)

set(UNQLITE_COMPILE_DEFINITIONS
	UNQLITE_ENABLE_THREADS
)

add_library(unqlite STATIC
	unqlite.c
	unqlite.h
)
set_target_properties(unqlite PROPERTIES
	COMPILE_DEFINITIONS "${UNQLITE_COMPILE_DEFINITIONS}"
)

set(UNQLITE_TESTS
	1
	2
	3
	4
	5
	6
	huge
	mp3
	tar
)

foreach(UNQLITE_TEST IN LISTS UNQLITE_TESTS)
	set(UNQLITE_TEST unqlite_${UNQLITE_TEST})
	add_executable(${UNQLITE_TEST} ${UNQLITE_TEST}.c)
	set_target_properties(${UNQLITE_TEST} PROPERTIES 
		COMPILE_DEFINITIONS "${UNQLITE_COMPILE_DEFINITIONS}"
		LINK_LIBRARIES unqlite
	)
endforeach()
