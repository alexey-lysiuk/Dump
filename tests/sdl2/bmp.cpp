#include <cstdio>
#include <stdio.h>
#include <SDL.h>

static void Convert(const char* filename)
{
	if (SDL_Surface* bmp = SDL_LoadBMP(filename))
	{
		if (SDL_SaveBMP(bmp, filename) != 0)
			printf("Failed to save %s\n", filename);

		SDL_FreeSurface(bmp);
	}
	else
		printf("Failed to load %s\n", filename);
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Usage: %s bmp-file ...\n", argv[0]);
		return 0;
	}

	if (SDL_Init(0) == 0)
	{
		for (int i = 1; i < argc; ++i)
			Convert(argv[i]);

		SDL_Quit();
	}
	else
	{
		puts("Failed to initialize SDL");
		return 1;
	}

	return 0;
}
