ifeq ($(TERM), xterm-256color)
	OUT=a.out
	CLEAN=rm
	CLEAR=clear
else
	OUT=a.exe
	CLEAN=del
	CLEAR=cls
endif

CC=g++
ROOT=../../
INCLUDES=$(ROOT)rubik/*.cpp $(ROOT)rubik/auxiliares/*.cpp $(ROOT)rubik/scores/*.cpp $(ROOT)rubik/scores/basic-score/*.cpp $(ROOT)managers/*.cpp $(ROOT)sqlite/*.o
LIBS=-fopenmp
O=

all:
	g++ tuning.cpp $(O) -o tuning.out