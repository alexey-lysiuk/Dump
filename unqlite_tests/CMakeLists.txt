cmake_minimum_required( VERSION 3.1.0 )

project(unqlite_tests)

set(UNQLITE_COMPILE_DEFINITIONS
	JX9_DISABLE_BUILTIN_FUNC
	JX9_DISABLE_DISK_IO
	UNQLITE_ENABLE_THREADS
)

add_library(unqlite STATIC
	unqlite.c
	unqlite.h
)
set_target_properties(unqlite PROPERTIES
	COMPILE_DEFINITIONS ${UNQLITE_COMPILE_DEFINITIONS}
)

add_executable(unqlite_huge unqlite_huge.c)
set_target_properties(unqlite_huge PROPERTIES 
	COMPILE_DEFINITIONS ${UNQLITE_COMPILE_DEFINITIONS}
	LINK_LIBRARIES unqlite
)
