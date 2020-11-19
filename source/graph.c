#include "graph.h"
#include "bmp.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>

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

static double expr_solve(lua_State* L, const char* expr, double x_value){
	lua_pushnumber(L, x_value);
	lua_setglobal(L, "x");
	char new_expr[256] = "value = ";
	strcat(new_expr, expr);
	luaL_dostring(L, new_expr);
	lua_getglobal(L, "value");
	return lua_tonumber(L, -1);
}

static void graph_drawGrid(bmp* image, graph_options option){
	if(option.show_grid == 0) return;
	for(int i = 0; i < option.width; i+= option.width/option.num_cols){
		bmp_drawLine(image, i, 0, i, option.height, option.grid_thickness, option.grid_color);
	}
	for(int i = 0; i < option.height; i+= option.height/option.num_lines){
		bmp_drawLine(image, 0, i, option.width, i, option.grid_thickness, option.grid_color);
	}
	{
		bmp_drawLine(image, 0, option.height/2, option.width, option.height/2, option.grid_thickness, option.axis_color);
		bmp_drawLine(image, option.width/2, 0, option.width/2, option.height, option.grid_thickness, option.axis_color);
	}
}

void graph_generate(graph_options option){
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	bmp* image = bmp_create(option.width, option.height);
	bmp_clear(image, option.bg);
	graph_drawGrid(image, option);
	double old_pixel_y = -1;
	old_pixel_y = -expr_solve(L, option.expr, -option.num_cols/2)*option.height/option.num_lines+option.height/2;
	for(int i = -option.width/2; i < option.width/2; i++){ // draw the function
		double x_value = (double)i/option.width*option.num_cols;
		double y_value = expr_solve(L, option.expr, x_value);
		y_value*=option.height/option.num_lines; y_value+=option.height/2;
		if((y_value < 0 || y_value > option.height) && (old_pixel_y < 0 || old_pixel_y > option.height)) continue;
		double pixel_x = i+option.width/2;
		double pixel_y = option.height-y_value;
		bmp_drawLine(image, pixel_x, pixel_y, pixel_x-1, old_pixel_y, option.line_thickness, option.fg);
		old_pixel_y = pixel_y;
	}
	bmp_saveAs(image, option.filename);
	lua_close(L);
}

