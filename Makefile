CC = gcc
CFLAGS = -Wall -pedantic -ansi `sdl-config --cflags`
LDFLAGS = `sdl-config --libs`
SRC = vector.c main.c
OBJ = $(SRC:.c=.o)

all: rayc

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

rayc: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ) rayc

.PHONY: clean all
