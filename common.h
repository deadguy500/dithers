#ifndef _COMMON_H_
#define _COMMON_H_

void rgbToHsb(int r, int g, int b, float* hue, float* saturation, float* brightness); 
float brightness(uint32_t rgb);

#endif