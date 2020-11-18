#include "bmp.h"
#include "graph.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	graph_options option = read_arguments(argc, argv);
	if(option.expr == NULL){
		printf("no expression\n");
		exit(EXIT_FAILURE);
	}
	char default_filename[] = "image.tga";
	if(option.filename == NULL) option.filename = default_filename;
	graph_generate(option);
	return 0;
}
