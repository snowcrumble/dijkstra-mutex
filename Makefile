OS = $(shell uname -s | tr A-Z a-z)

ifeq ($(OS), linux)
	CC=g++
	CFLAGS=-O0 -std=c++11 -pthread -Wl,--no-as-needed
else ifeq ($(OS), darwin)
	CC=clang++
	CFLAGS=-O0 -std=c++2a
endif

all:
	$(CC) $(CFLAGS) lock.cpp -o lock