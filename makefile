CC = g++
DEBUG = -g
CFLAGS = -Wall $(DEBUG) -std=c++11 -pthread

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
CFLAGS += -DLINUX
endif

.PHONY: clean

CPPrime: CPPrime.cpp
	make clean
	$(CC) -pthread -o CPPrime.o CPPrime.cpp $(LIBS)

clean:
	rm -f CPPrime.o
