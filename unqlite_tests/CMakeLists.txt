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

function(add_unqlite_test test_name)
	add_executable(${test_name} ${test_name}.c)
	set_target_properties(${test_name} PROPERTIES 
		COMPILE_DEFINITIONS "${UNQLITE_COMPILE_DEFINITIONS}"
		LINK_LIBRARIES unqlite
	)
endfunction()

add_unqlite_test(unqlite_huge)
add_unqlite_test(unqlite_tar)
