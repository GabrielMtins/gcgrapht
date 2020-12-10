# gcgrapht
gcgrapht - Generates a graph as a .ff (farbfeld) file  

## Synopsis
gcgrapht [OPTION] ... [FUNCTION]   

## Dependencies

libgffimage - https://github.com/GabrielMtins/libgffimage

## Installation
```
$ git clone https://github.com/GabrielMtins/gcgrapht.git
$ cd gcgrapht
$ make
$ sudo make install
```
## Description
Generates a graph as a .ff file  
If there is not a function, it will read the standard input  
```
-gs, --grid-size
Selects the size of the grid of the graph
Example: -gs 16x16
	
-s, --size
Selects the size of the image in pixels
Example: -s 1024x1024
	
-sg, --show-grid
If true, show grid marks, if false, it doesnt show it
Example: -sg false
	
-lt, --line-thickness
Set the thickness of the graph's line in pixels
Example: -lt 4

-gt, --grid-thickness
Set the thickness of the grid marks in pixels
The thickness of the x and y axis will always be doubled the 
thickness of the grid
Example: -gt 4

-bg, --background
Set the background color
The color needs to be in hexadecimal
Example: -bg 00FF00 (set the color to green)
-bg FF0000 (set the color to red)

-fg, --foreground
Set the foreground color (line color)
The color needs to be in hexadecimal
Example: -fg FF0000 (set the color to red)

-gc, --grid-color
Set the grid color
The color needs to be in hexadecimal
Example: -fg FF0000 (set the color to red)

-ac, --axis-color
Set the xy axis color
The color needs to be in hexadecimal
Example: -fg FF0000 (set the color to red)

-o, --output
Set the output file
If not set, the output file will be image.ff

-help
Display a help message 
```

## Examples
```
$ gcgrapht "2*x+1" - creates the graph of f(x) = 2x+1  
$ gcgrapht "x^2" -o graph.ff - creates the graph of f(x) = x^2 and saves it to the graph.ff file  
```
Here's a simple example using unix pipelines (since the program can read from the stdin)   
```
$ echo -e "x^2-1\n2^x+1" > func.txt
$ cat func.txt | gcgrapht
$ ff2png < image.ff > image.png
```
## Author
Written by Gabriel Martins   

## Copyright
Copyright (C) Gabriel Martins 2020. License GPLv3+: GNU GPL Version 3 or later. This is free software. You are free to change and redistribute it.   
There is NO WARRANTY, to the extent permited by law.   

Copyright © 1994–2019 Lua.org, PUC-Rio.   
(This program uses the Lua C API to generate graphs)   
