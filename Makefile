CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi
LDFLAGS = -lm
SRC = vector.c ray.c render.c sphere.c main.c
OBJ = $(SRC:.c=.o)
OS = $(shell uname)

ifeq ($(OS), Darwin)
else
	CFLAGS += -fopenmp
	LDFLAGS += -fopenmp
endif


all: rayc

test: all
	./rayc

debug: CFLAGS += -g
debug: all

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

rayc: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ) rayc

.PHONY: clean all debug test
