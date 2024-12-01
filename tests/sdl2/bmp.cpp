#include <stdio.h>
#include <SDL.h>

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("Usage: %s bmp-in bmp-out\n", argv[0]);
		return 0;
	}

	if (SDL_Init(0) == 0)
	{
		puts("SDL initialized");

		if (SDL_Surface* bmp = SDL_LoadBMP(argv[1]))
		{
			printf("%s opened\n", argv[1]);

			if (SDL_SaveBMP(bmp, argv[2]) == 0)
			{
				printf("%s saved\n", argv[2]);
			}

			SDL_FreeSurface(bmp);
		}

		SDL_Quit();
	}

	return 0;
}
