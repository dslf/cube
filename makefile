CC=gcc
CPFLAGS=-ansi

all: test 

test: main.c
	$(CC) $(CFLAGS) -o cube main.c defee39.c

clean:
	del cube.exe
