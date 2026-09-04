CC=g++
SOURCES=*.cpp

all:
	$(CC) -o js -std=c++23 -Wall -Wextra -Werror $(SOURCES)
