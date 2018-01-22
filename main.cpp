
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "dither_rnd.h"

#define SCREEN_WIDTH		605
#define SCREEN_HEIGHT		454

SDL_Surface* loadSurface(char* path, SDL_PixelFormat* format)
{
	SDL_Surface* convertedSurface = NULL;
	SDL_Surface* imageSurface = IMG_Load(path);

	if(imageSurface == NULL)
	{
		printf("Unable to load image");
	}
	else
	{
		convertedSurface = SDL_ConvertSurface(imageSurface, format, 0 );

		if(convertedSurface == NULL)
		{
			printf("Unable to convert image");
		}

		SDL_FreeSurface(imageSurface);
	}

	return convertedSurface;
}

int main( int argc, char* args[] )
{
	srand(time(0));

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return -1;
	}
	
	SDL_Window* mainWindow = SDL_CreateWindow("Dither tests", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, 
		SCREEN_HEIGHT, 
		SDL_WINDOW_SHOWN);
	
	if( mainWindow == NULL)
	{
		return -1;
	}

	int imgFlags = IMG_INIT_PNG;

	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		return -1;
	}
	
	SDL_Surface* screen = SDL_GetWindowSurface(mainWindow);	
	SDL_Surface* image = loadSurface("../data/kitten.png", screen->format);

	if(image == NULL)
	{
		printf("Failed to load image!\n");
		return -1;
	}

	bool quit = false;

	SDL_Event e;

	SDL_Surface* dither = randomDither(image);

	while(!quit)
	{
		while(SDL_PollEvent( &e ) != 0 )
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_BlitSurface(dither, NULL, screen, NULL);
		SDL_UpdateWindowSurface(mainWindow);
	}

	SDL_FreeSurface(image);
	image = NULL;

	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	SDL_FreeSurface(dither);
	dither = NULL;

	IMG_Quit();
	SDL_Quit();

	return 0;
}

