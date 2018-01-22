#include <SDL2/SDL.h>
#include <stdlib.h>


void rgbToHsb(int r, int g, int b, float* hue, float* saturation, float* brightness) 
{
	uint32_t cmax = 0.0;
	uint32_t cmin = 0.0;

	if (r > g)
	{
		cmax = r;
	}
	else
	{
		cmax = g;
	}

	if (b > cmax) 
	{
		cmax = b;
	}

	if (r < g)
	{
		cmin = r;
	}
	else
	{
		cmin = g;
	}

	if (b < cmin) 
	{
		cmin = b;
	}

	*brightness = ((float)cmax) / 255.0;

	if (cmax != 0)
	{
		*saturation = ((float)(cmax - cmin)) / ((float)cmax);
	}
 	else
    {
    	*saturation = 0;
    }

	if (*saturation == 0)
	{
		*hue = 0;
	}
 	else 
 	{
     	float redc = ((float)(cmax - r)) / ((float)(cmax - cmin));
     	float greenc = ((float)(cmax - g)) / ((float)(cmax - cmin));
     	float bluec = ((float)(cmax - b)) / ((float)(cmax - cmin));
     	
     	if (r == cmax)
        {
        	*hue = bluec - greenc;
        }
     	else if (g == cmax)
        {
        	*hue = 2.0 + redc - bluec;
     	}
     	else
        {
        	*hue = 4.0 + greenc - redc;
        }
     
     	*hue = *hue / 6.0;
    
    	if (*hue < 0)
        {
        	*hue = *hue + 1.0;
        }
 	}
}

float brightness(uint32_t rgb)
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	uint32_t r = (rgb & 0x00ff0000) >> 0;
	uint32_t g = (rgb & 0x0000ff00) >> 8;
	uint32_t b = (rgb & 0x000000ff) >> 16;
#else
	uint32_t r = (rgb & 0x000000ff) >> 0;
	uint32_t g = (rgb & 0x0000ff00) >> 8;
	uint32_t b = (rgb & 0x00ff0000) >> 16;
#endif

	float hue = 0.0; 
	float saturation = 0.0;
	float brightness = 0.0;

	rgbToHsb(r, g, b, &hue, &saturation, &brightness);

	return brightness * 255;
}
