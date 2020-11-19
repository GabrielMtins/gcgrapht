#ifndef BMP_H
#define BMP_H

#include <stddef.h>
#include <stdint.h>

/*
    Copyright (C) 2020  Gabriel Martins

    This file is part of gcgrapht.

    gcgrapht is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    gcgrapth is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with gcgrapht.  If not, see <https://www.gnu.org/licenses/>
    Contact: gabrielmartinsthe@gmail.com
*/

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
