cmake_minimum_required( VERSION 3.1.0 )

project(sdl_test)

find_package( SDL2 REQUIRED CONFIG )
include_directories( "${SDL2_INCLUDE_DIRS}" )
set( ZDOOM_LIBS ${ZDOOM_LIBS} "${SDL2_LIBRARIES}" )

CHECK_CXX_SOURCE_COMPILES("#include <SDL_version.h>
int main()
{
	#if !SDL_VERSION_ATLEAST(2, 0, 6)
	#error \"Only SDL 2.0.6 or later is supported.\"
	#endif
	return 0;
}" SDL2_MIN_VERSION )

if (NOT SDL2_MIN_VERSION)
	message(SEND_ERROR "Only SDL 2.0.6 or later is supported.")
endif()
