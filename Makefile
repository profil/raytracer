LDFLAGS=-lm
all: 
	$(CC) src/main.c `sdl-config --cflags --libs` $(LDFLAGS) -o bin/raytracer

