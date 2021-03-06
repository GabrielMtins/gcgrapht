#include "graph.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>
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

static double expr_solve(lua_State* L, const char* expr, double x_value);

static void graph_drawGrid(ffimage* image, graph_options option);

static void graph_drawExpression(ffimage* image, graph_options option, lua_State* L);

static int graph_readFromStdin(graph_options* option);

static double expr_solve(lua_State* L, const char* expr, double x_value){
	lua_pushnumber(L, x_value);
	lua_setglobal(L, "x");
	char new_expr[256] = "value = ";
	strcat(new_expr, expr);
	luaL_dostring(L, new_expr);
	lua_getglobal(L, "value");
	return lua_tonumber(L, -1);
}

static void graph_drawGrid(ffimage* image, graph_options option){
	if(option.show_grid == 0) return;
	for(int i = 0; i < option.width; i+= option.width/option.num_cols){ // draw grids
		ffimage_drawLine(image, i, 0, i, option.height, option.grid_thickness, option.grid_color);
	}
	for(int i = 0; i < option.height; i+= option.height/option.num_lines){
		ffimage_drawLine(image, 0, i, option.width, i, option.grid_thickness, option.grid_color);
	}
	{ // draw axis
		ffimage_drawLine(image, 0, option.height/2, option.width, option.height/2, option.grid_thickness*2, option.axis_color);
		ffimage_drawLine(image, option.width/2, 0, option.width/2, option.height, option.grid_thickness*2, option.axis_color);
	}
}

static void graph_drawExpression(ffimage* image, graph_options option, lua_State* L){
	double old_pixel_y = -1;
	old_pixel_y = -expr_solve(L, option.expr, -option.num_cols/2)*option.height/option.num_lines+option.height/2;

	for(int i = -option.width/2; i < option.width/2; i++){
		double x_value = (double)i/option.width*option.num_cols;
		double y_value = expr_solve(L, option.expr, x_value);
		y_value*=option.height/option.num_lines; y_value+=option.height/2;
		if((y_value < 0 || y_value > option.height) && (old_pixel_y < 0 || old_pixel_y > option.height)) continue;
		double pixel_x = i+option.width/2;
		double pixel_y = option.height-y_value;
		ffimage_drawLine(image, pixel_x, pixel_y, pixel_x-1, old_pixel_y, option.line_thickness, option.fg);
		old_pixel_y = pixel_y;
	}

	if(!strcmp(option.filename, "stdout")) ffimage_saveToOutput(image);
	else ffimage_saveAs(image, option.filename);
}

static int graph_readFromStdin(graph_options* option){
	size_t len = 0;
	return getline(&option->expr, &len, stdin) != -1;
}

void graph_generate(graph_options option){
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	ffimage* image = ffimage_create(option.width, option.height);
	ffimage_clear(image, option.bg);
	graph_drawGrid(image, option);

	if(option.expr == NULL){
		while(graph_readFromStdin(&option)){
			graph_drawExpression(image, option, L);
		}
		free(option.expr);
	}
	else{
		graph_drawExpression(image, option, L);
	}

	lua_close(L);
	ffimage_destroy(image);
}
