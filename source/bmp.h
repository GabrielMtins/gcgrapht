#ifndef BMP_H
#define BMP_H

#include <stddef.h>
#include <stdint.h>

typedef struct{
	uint8_t* buffer;
	int width, height;
} bmp;

typedef struct{
	uint8_t r, g, b;
} color;

bmp* bmp_create(int width, int height);

void bmp_clear(bmp* self, color c);

void bmp_drawPixel(bmp* self, int i, int j, color c);

void bmp_drawRect(bmp* self, int x, int y, int w, int h, color c);

void bmp_drawLine(bmp* self, int x1, int y1, int x2, int y2, int thickness, color c);

void bmp_saveAs(bmp* self, const char* filename);

#endif
