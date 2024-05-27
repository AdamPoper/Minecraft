CC=gcc
CFLAGS=-g -Wall -framework Cocoa -framework OpenGL -framework IOKit

INC=-I/usr/local/include -Idependencies/include

SRC=$(wildcard src/*.c) $(wildcard src/cglm/*.c) $(wildcard src/util/*.c) $(wildcard src/renderer/*.c) $(wildcard src/world/*.c)
EXE=$(SRC:.c=)

APP_LINKERS=-Ldependencies/lib/GLFW -lglfw3

all: everything

everything: $(SRC)
	$(CC) $(CFLAGS) $(INC) $(APP_LINKERS) -o run $(SRC)

glad.o: src/glad.c
	$(CC) $(CFLAGS) $(INC) -c src/glad.c -o glad.o

clean:
	rm run *.o
