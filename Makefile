
# Copyright (C) 2020  Gabriel Martins

# This file is part of gcgrapht.

# gcgrapht is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# gcgrapth is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
    
# You should have received a copy of the GNU General Public License
# along with gcgrapht.  If not, see <https://www.gnu.org/licenses/>
# Contact: gabrielmartinsthe@gmail.com

CC = gcc
EXEC ?= gcgrapht

CCFLAGS := -Wall -Wextra -O2

LIBFLAGS := -llua -lm -ldl

SRC_DIR := source

BUILD_DIR := ./build

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(addprefix $(BUILD_DIR)/, $(SRC))
OBJECTS := $(addsuffix .o, $(OBJECTS))

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@ $(CCFLAGS)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CCFLAGS) $(LIBFLAGS) -o $(EXEC)

install:
	cp $(EXEC) /usr/bin/$(EXEC)

clean:
	rm -r build
	rm $(EXEC)
