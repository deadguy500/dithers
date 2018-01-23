
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "dither_rnd.h"
#include "floyd_steinberg.h"

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

	SDL_Surface* rndDither = randomDither(image);
	SDL_Surface* fsDither = floydSteinberg(image);

	uint32_t ditherState = 0;

	while(!quit)
	{
		while(SDL_PollEvent( &e ) != 0 )
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (e.type == SDL_KEYDOWN)
		    {
		        if (e.key.keysym.sym == SDLK_ESCAPE)
		        {
		            quit = true;
		        }
				else if(e.key.keysym.sym == SDLK_F1)
				{
					ditherState = 0;
				}
				else if(e.key.keysym.sym == SDLK_F2)
				{
					ditherState = 1;					
				}
				else if(e.key.keysym.sym == SDLK_F3)
				{
					ditherState = 2;
				}
				else if(e.key.keysym.sym == SDLK_F4)
				{
					ditherState = 3;
				}
			}
		}

		switch(ditherState)
		{
			case 1:
				SDL_BlitSurface(rndDither, NULL, screen, NULL);
				break;

			case 2:
				if(rndDither != NULL)
				{
					SDL_FreeSurface(rndDither);
					rndDither = NULL;
				}
				
				rndDither = randomDither(image);
				SDL_BlitSurface(rndDither, NULL, screen, NULL);
				break;

			case 3:
				SDL_BlitSurface(fsDither, NULL, screen, NULL);
				break;

			case 0:
			default:
				SDL_BlitSurface(image, NULL, screen, NULL);
				break;
		}

		SDL_UpdateWindowSurface(mainWindow);
	}

	SDL_FreeSurface(image);
	image = NULL;

	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	SDL_FreeSurface(rndDither);
	rndDither = NULL;

	SDL_FreeSurface(fsDither);
	fsDither = NULL;

	IMG_Quit();
	SDL_Quit();

	return 0;
}

