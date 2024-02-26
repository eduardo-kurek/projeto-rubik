CC=g++
O=-O3
ROOT=../../../../
AUXILIARES = $(filter-out $(ROOT)rubik/auxiliares/StickerCoord.cpp, $(wildcard $(ROOT)rubik/auxiliares/*.cpp))
INCLUDES=$(ROOT)rubik/*.cpp $(ROOT)rubik/auxiliares/StickerCoord.cpp $(AUXILIARES) $(ROOT)rubik/scores/*.cpp $(ROOT)rubik/scores/basic-score/*.cpp

all:
	$(CC) tuning.cpp $(O) $(INCLUDES) -fopenmp -o tuning.out