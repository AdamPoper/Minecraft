CC=gcc
CFLAGS=-g -Wall -lglfw -framework OpenGL

INC=-I/usr/local/include -Idependencies/include

SRC=$(wildcard src/*.c) $(wildcard src/cglm/*.c) $(wildcard src/util/*.c) $(wildcard src/renderer/*.c)
EXE=$(SRC:.c=)

all: everything

everything: $(SRC)
	$(CC) $(CFLAGS) $(INC) -o run $(SRC)

glad.o: src/glad.c
	$(CC) $(CFLAGS) $(INC) -c src/glad.c -o glad.o

clean:
	rm run *.o
