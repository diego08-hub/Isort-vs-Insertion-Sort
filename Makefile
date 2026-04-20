CC = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra -pedantic

all: experimento

experimento: experimento.c
	$(CC) $(CFLAGS) -o experimento experimento.c

clean:
	rm -f experimento