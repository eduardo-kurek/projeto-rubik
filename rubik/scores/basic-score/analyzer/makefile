ifeq ($(TERM), xterm-256color)
	OUT=a.out
	CLEAN=rm
	CLEAR=clear
else
	OUT=a.exe
	CLEAN=del
	CLEAR=cls
endif

CC=g++ -std=c++17
ROOT=../../../../
AUXILIARES = $(filter-out $(ROOT)rubik/auxiliares/StickerCoord.cpp, $(wildcard $(ROOT)rubik/auxiliares/*.cpp))
INCLUDES=$(ROOT)rubik/** $(ROOT)rubik/auxiliares/*.cpp $(ROOT)rubik/scores/*.cpp $(ROOT)rubik/scores/basic-score/*.cpp
LIBS=-fopenmp
O=-O3

all:
	$(CC) main.cpp $(INCLUDES) $(LIBS) -o analysis.out $(O)

make tun:
	g++ tuning.cpp $(O) -o tuning.out
	
run-default:
	./analysis.out 3 2 2 1 0 3 2 1 0