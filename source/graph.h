#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include <gffimage/ffimage.h>

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
	int width, height;
	int num_cols, num_lines;
	int line_thickness;
	int show_grid;
	ffcolor bg, fg; //foreground and background
	char* expr;
	char* filename;
	ffcolor grid_color;
	ffcolor axis_color;
	int grid_thickness;
} graph_options;

void graph_generate(graph_options option);

#endif
