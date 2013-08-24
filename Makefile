CC = gcc
UNAME = $(shell uname)


all: 
	$(CC) main.c `sdl-config --cflags --libs` -o raytracer

