#include "bmp.h"
#include "graph.h"
#include "util.h"
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

int main(int argc, char** argv){
	graph_options option = read_arguments(argc, argv);
	char default_filename[] = "image.tga";
	if(option.filename == NULL) option.filename = default_filename;
	graph_generate(option);
	return 0;
}
