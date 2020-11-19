#include "bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

bmp* bmp_create(int width, int height){
	bmp* self = malloc(sizeof(bmp));
	self->width = width;
	self->height = height;
	self->buffer = malloc(width*height*3);
	return self;
}

void bmp_clear(bmp* self, color c){
	for(int i = 0; i < self->width; i++){
		for(int j = 0; j < self->height; j++){
			bmp_drawPixel(self, i, j, c);
		}
	}
}

void bmp_drawPixel(bmp* self, int i, int j, color c){
	if(i < 0 || j < 0 || i >= self->width || j >= self->height) return;
	self->buffer[3*(i+j*self->width)+0] = c.b;
	self->buffer[3*(i+j*self->width)+1] = c.g;
	self->buffer[3*(i+j*self->width)+2] = c.r;
}

void bmp_drawLine(bmp* self, int x1, int y1, int x2, int y2, int thickness, color c){
	double dx = (x2-x1);
	double dy = (y2-y1);
	double steps = 0;
	if(fabs(dx) > fabs(dy)) steps = fabs(dx);
	else steps = fabs(dy);
	double start_x = x1, start_y = y1;
	for(int i = 0; i < steps; i++){
		start_x+=(double)dx/steps;
		start_y+=(double)dy/steps;
		if(start_x < 0 || start_y < 0 || start_x > self->width || start_y > self->height) return;
		bmp_drawRect(self, start_x, start_y, thickness, thickness, c);
	}
}

void bmp_drawRect(bmp* self, int x, int y, int w, int h, color c){
	for(int i = 0; i < w; i++){
		for(int j = 0; j < h; j++){
			bmp_drawPixel(self, x+i, y+j, c);
		}
	}
}

void bmp_saveAs(bmp* self, const char* filename){
	FILE* file = fopen(filename, "wb");
	if(file == NULL){
		printf("failed to open file\n");
		exit(-1);
	}
	uint8_t header[18] = {};
	header[2] = 2;
	header[12] = 255 & self->width;
	header[13] = 255 & (self->width>>8);
	header[14] = 255 & self->height;
	header[15] = 255 & (self->height>>8);
	header[16] = 24;
	header[17] = 32;
	fwrite(header, 18, 1, file);
	fwrite(self->buffer, self->width*self->height*3, 1, file);
	fclose(file);
}
