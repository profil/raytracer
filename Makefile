CC = gcc
CFLAGS = -Wall -pedantic -ansi
LDFLAGS = -lm
SRC = vector.c ray.c render.c sphere.c main.c
OBJ = $(SRC:.c=.o)

all: rayc

debug: CFLAGS += -g
debug: all

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

rayc: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ) rayc

.PHONY: clean all debug
