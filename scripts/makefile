ifeq ($(TERM), xterm-256color)
	OUT=a.out
	CLEAN=rm
	CLEAR=CLEAR
else
	OUT=a.exe
	CLEAN=del
	CLEAR=cls
endif

CC=g++
ROOT=../
INCLUDES=$(ROOT)rubik/*.cpp $(ROOT)rubik/auxiliares/*.cpp $(ROOT)rubik/scores/*.cpp
LIBS=-fopenmp

populate-scrambles:
	$(CC) scrambles.cpp $(INCLUDES) $(LIBS) -o scrambles.out