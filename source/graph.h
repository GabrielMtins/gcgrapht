#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include "bmp.h"

typedef struct{
	int width, height;
	int num_cols, num_lines;
	int line_thickness;
	int show_grid;
	color bg, fg; //foreground and background
	char* expr;
	char* filename;
	color grid_color;
	color axis_color;
	int grid_thickness;
} graph_options;

void graph_generate(graph_options option);

#endif
