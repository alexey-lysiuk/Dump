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

#include <cstdio>
#include <cstdlib>

#include <SDL.h>
#include <physfs.h>


static void QuitPhysFS()
{
	if (0 == PHYSFS_deinit())
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Unable to shutdown PhysicsFS: %s", PHYSFS_getLastError());
	}
}

bool InitSDL()
{
	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "ERROR! Unable to initialize SDL: %s\n", SDL_GetError());
		return false;
	}
	
	atexit(SDL_Quit);
	
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
	
	return true;
}

bool InitPhysicsFS(const char* args)
{
	if (0 == PHYSFS_init(args))
	{
		SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "Unable to initialize PhysicsFS: %s", PHYSFS_getLastError());
		return false;
	}

	atexit(QuitPhysFS);

	return true;
}

int MountPackage(const char* path)
{
	if (0 == PHYSFS_mount(path, nullptr, 0))
	{
		SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "Unable to mount package '%s': %s", path, PHYSFS_getLastError());
		return false;
	}
	
	return true;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Usage: %s doom2rpg.ipa\n", argv[0]);
		return EXIT_SUCCESS;
	}

	const bool success = InitSDL()
		&& InitPhysicsFS(argv[0])
		&& MountPackage(argv[1]);
	
	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
