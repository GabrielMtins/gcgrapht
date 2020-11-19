#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR_CHECKING_NUM(str, var) if(!sscanf(str, "%i", &var)){printf("Argument is not a number\n"); exit(EXIT_FAILURE);}
#define ERROR_CHECKING_BOUND(i, argc) if(i >= argc){printf("No argument\n"); exit(EXIT_FAILURE);}

static color getColorFromInt(unsigned int color_int){
	color c = {
		color_int&0xff,
		(color_int>>8)&0xff,
		(color_int>>16)&0xff
	};
	return c;
}
static color color_sscanf(char* argv){
	unsigned int color;
	if(!sscanf(argv, "%x", &color)){
		printf("Argument is not a valid color\n");
		exit(EXIT_FAILURE);	
	}
	return getColorFromInt(color);
}

graph_options read_arguments(int argc, char** argv){
	graph_options option = {
		512, 512,
		16, 16,
		2,
		1,
		{0x00, 0x00, 0x00},
		{0x64, 0x00, 0xde},
		NULL, NULL,
		{0x80, 0x80, 0x80},
		{0xff, 0xff, 0xff},
		1
	};
	if(argc == 1) return option;
	for(int i = 1; i < argc; i++){
		if(!strcmp(argv[i], "--grid-size") || !strcmp(argv[i], "-gs")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			if(!sscanf(argv[i], "%ix%i", &option.num_cols, &option.num_lines)){
				printf("Argument is not a number\n");
				exit(EXIT_FAILURE);
			}
			continue;
		}
		if(!strcmp(argv[i], "--size") || !strcmp(argv[i], "-s")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			if(!sscanf(argv[i], "%ix%i", &option.width, &option.height)){
				printf("Argument is not a number\n"); exit(EXIT_FAILURE);
			}
			continue;
		}
		if(!strcmp(argv[i], "--show-grid") || !strcmp(argv[i], "-sg")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			if(!strcmp(argv[i], "true")) option.show_grid = 1;
			else option.show_grid = 0;
			continue;
		}
		if(!strcmp(argv[i], "--line-thickness") || !strcmp(argv[i], "-lt")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			ERROR_CHECKING_NUM(argv[i], option.line_thickness);
			continue;
		}
		if(!strcmp(argv[i], "--grid-thickness") || !strcmp(argv[i], "-gt")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			ERROR_CHECKING_NUM(argv[i], option.grid_thickness);
			continue;
		}
		if(!strcmp(argv[i], "--background") || !strcmp(argv[i], "-bg")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			option.bg = color_sscanf(argv[i]);
			continue;
		}
		if(!strcmp(argv[i], "--foreground") || !strcmp(argv[i], "-fg")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			option.fg = color_sscanf(argv[i]);
			continue;
		}
		if(!strcmp(argv[i], "--grid-color") || !strcmp(argv[i], "-gc")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			option.grid_color = color_sscanf(argv[i]);
			continue;
		}
		if(!strcmp(argv[i], "--axis-color") || !strcmp(argv[i], "-ac")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			option.axis_color = color_sscanf(argv[i]);
			continue;
		}
		if(!strcmp(argv[i], "--output") || !strcmp(argv[i], "-o")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			option.filename = argv[i];
			continue;
		}
		option.expr = argv[i];
	}
	return option;
}
