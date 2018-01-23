#ifndef _COMMON_H_
#define _COMMON_H_

#define REV_RGBA(a)			((a & 0x000000ff) << 24) | ((a & 0x0000ff00) << 8) | ((a & 0x00ff0000) >> 8) | ((a & 0xff000000) >> 24)


uint32_t getPixel(SDL_Surface* s, int x, int y);
void setPixel(SDL_Surface* s, int x, int y, uint32_t p);
void setPixelRgb(SDL_Surface* s, int x, int y, uint8_t r, uint8_t g, uint8_t b);

void rgbToHsb(int r, int g, int b, float* hue, float* saturation, float* brightness); 
float brightness(uint32_t rgb);

#endif