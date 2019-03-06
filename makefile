IDIR = ./
CC = g++
CFLAGS = -I$(IDIR)

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
CFLAGS += -DLINUX
endif

CPPrime: CPPrime.cpp
  make clean
  $(CC) -o CPPrime.o CPPrime.cpp $(CFLAGS)
  
.PHONY: clean

clean:
  rm -f CPPrime.o
