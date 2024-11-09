CC=gcc
CPFLAGS=-std=c89 -Wall

all: test 

test: main.c
	$(CC) $(CFLAGS) -o skrambilka main.c defee39.c

clean:
	del skrambilka.exe
