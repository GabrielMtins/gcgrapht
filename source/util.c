#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

#define ERROR_CHECKING_NUM(str, var) if(!sscanf(str, "%i", &var)){printf("Argument is not a number\n"); exit(EXIT_FAILURE);}
#define ERROR_CHECKING_BOUND(i, argc) if(i >= argc){printf("No argument\n"); exit(EXIT_FAILURE);}

static ffcolor getColorFromInt(unsigned int color_int);

static ffcolor color_sscanf(char* argv);

static ffcolor getColorFromInt(unsigned int color_int){
	ffcolor c = {
		(color_int>>16)&0xff,
		(color_int>>8)&0xff,
		color_int&0xff,
		255
	};
	return c;
}
static ffcolor color_sscanf(char* argv){
	unsigned int color;
	if(!sscanf(argv, "%x", &color)){
		printf("Argument is not a valid color\n");
		exit(EXIT_FAILURE);	
	}
	return getColorFromInt(color);
}

graph_options read_arguments(int argc, char** argv){
	graph_options option = {
		1024, 1024,
		16, 16,
		4,
		2,
		{0x00, 0x00, 0x00, 0xff},
		{0x64, 0x00, 0xde, 0xff},
		NULL, NULL,
		{0x80, 0x80, 0x80, 0xff},
		{0xff, 0xff, 0xff, 0xff},
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
		}
		else if(!strcmp(argv[i], "--size") || !strcmp(argv[i], "-s")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			if(!sscanf(argv[i], "%ix%i", &option.width, &option.height)){
				printf("Argument is not a number\n"); exit(EXIT_FAILURE);
			}
		}
		else if(!strcmp(argv[i], "--show-grid") || !strcmp(argv[i], "-sg")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			if(!strcmp(argv[i], "true")) option.show_grid = 1;
			else option.show_grid = 0;
		}
		else if(!strcmp(argv[i], "--line-thickness") || !strcmp(argv[i], "-lt")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			ERROR_CHECKING_NUM(argv[i], option.line_thickness);
		}
		else if(!strcmp(argv[i], "--grid-thickness") || !strcmp(argv[i], "-gt")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			ERROR_CHECKING_NUM(argv[i], option.grid_thickness);
		}
		else if(!strcmp(argv[i], "--background") || !strcmp(argv[i], "-bg")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			option.bg = color_sscanf(argv[i]);
		}
		else if(!strcmp(argv[i], "--foreground") || !strcmp(argv[i], "-fg")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			option.fg = color_sscanf(argv[i]);
		}
		else if(!strcmp(argv[i], "--grid-color") || !strcmp(argv[i], "-gc")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			option.grid_color = color_sscanf(argv[i]);
		}
		else if(!strcmp(argv[i], "--axis-color") || !strcmp(argv[i], "-ac")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			option.axis_color = color_sscanf(argv[i]);
		}
		else if(!strcmp(argv[i], "--output") || !strcmp(argv[i], "-o")){
			i++;
			ERROR_CHECKING_BOUND(i, argc);
			option.filename = argv[i];
		}
		else if(!strcmp(argv[i], "-help")){
			printf(
			"Copyright (C) Gabriel Martins 2020\nThis program comes with absolutely NO WARRANTY\nThis is free software and you are welcome to redistribute it\nunder certain conditions\nAlso copyright notice to:\nCopyright © 1994–2019 Lua.org, PUC-Rio.\n");
			exit(EXIT_SUCCESS);
		}
		else option.expr = argv[i];
	}
	return option;
}
