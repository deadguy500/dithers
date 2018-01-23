#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"

SDL_Surface* randomDither(SDL_Surface* src)
{
	uint32_t rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

	SDL_Surface* dest = SDL_CreateRGBSurface(0, src->w, src->h, 32, rmask, gmask, bmask, amask);

	for (uint32_t x = 0; x < src->w; x++) 
	{
		for (uint32_t y = 0; y < src->h; y++) 
		{
			uint32_t p = getPixel(src, x, y);
			float bn = brightness(p);
			int32_t rnd = (rand() % 128) - 64;
			
			int32_t k = ((int32_t)ceil(bn)) + rnd;
			
			if (k < 128) 
			{
				setPixelRgb(dest, x, y, 0x00, 0x00, 0x00);
			}
			else 
			{
				setPixelRgb(dest, x, y, 0xff, 0xff, 0xff);
			}
		}
	}

	return dest;
}
