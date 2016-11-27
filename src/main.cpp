/*
 * Doom II RPG
 * Copyright (C) 2016  Alexey Lysiuk

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>

#include <SDL.h>
#include <physfs.h>


static void QuitPhysFS()
{
	PHYSFS_deinit();
}

int main(int argc, char** argv)
{
	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "ERROR! Unable to initialize SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	atexit(SDL_Quit);
	
	if (0 == PHYSFS_init(argv[0]))
	{
		SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "Unable to initialize PhysicsFS: %s", PHYSFS_getLastError());
		return EXIT_FAILURE;
	}
	
	atexit(QuitPhysFS);
	
	return EXIT_SUCCESS;
}
