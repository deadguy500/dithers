#include <SDL2/SDL.h>
#include "common.h"

static uint8_t colorLimit(int32_t c)
{
	if(c > 255)
	{
		return 255;
	}
	else if(c < 0)
	{
		return 0;
	}

	return (uint8_t)c;
}

static void ditherPixel(SDL_Surface* sf, uint32_t x, uint32_t y, float e)
{
	uint32_t pixel = getPixel(sf, x, y);
	float brigh = brightness(pixel);
	int32_t color = floor(brigh + e);
	uint8_t comp = colorLimit(color);
	setPixelRgb(sf, x, y, comp, comp, comp);
}

SDL_Surface* floydSteinberg(SDL_Surface* src)
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

    SDL_Surface* tmp = SDL_CreateRGBSurface(0, src->w, src->h, 32, rmask, gmask, bmask, amask);
    SDL_BlitSurface(src, NULL, tmp, NULL);

	SDL_Surface* dest = SDL_CreateRGBSurface(0, src->w, src->h, 32, rmask, gmask, bmask, amask);

	for (uint32_t x = 0; x < tmp->w; x++) 
	{
		for (uint32_t y = 0; y < tmp->h; y++) 
		{
			uint32_t p = getPixel(tmp, x, y);
			float bn = brightness(p);
			uint32_t t = 0x00;

			if (bn >= 128) 
			{
				t = 0xff;
			}      

			int32_t err = ceil(bn - t);

			setPixelRgb(dest, x+1, y+0, t, t, t);

			if(x < tmp->w-1)
			{
				ditherPixel(tmp, x+1, y, (7.0/16 * err));
			}
			else
			{
				setPixel(tmp, x+1, y+0, 0xff000000);
			}

			if(x > 0 && y < tmp->h-1)
			{
				ditherPixel(tmp, x-1, y+1, 3.0/16 * err);
			}
			else
			{
				setPixel(tmp, x-1, y+1, 0xff000000);
			}

			if(y < tmp->h-1)
			{
				ditherPixel(tmp, x, y+1, 5.0/16 * err);	
			}
			else
			{
				setPixel(tmp, x+0, y+1, 0xff000000);
			}

			if(x < tmp->w-1 && y < tmp->h-1)
			{
				ditherPixel(tmp, x+1, y+1, 1.0/16 * err);
			}
			else
			{
				setPixel(tmp, x+1, y+1, 0xff000000);
			}
		}
	}

	SDL_FreeSurface(tmp);
	tmp = NULL;

	return dest;
}