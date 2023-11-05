CC=g++
CFLAGS=-Wall -Wextra -ggdb -Iinclude -std=c++23
LIBS=-lfmt

all:
	mkdir -p build
	$(CC) $(CFLAGS) src/*.cpp -o ./build/apx $(LIBS)