ifeq ($(TERM), xterm-256color)
	OUT=a.out
	CLEAN=rm
	CLEAR=clear
else
	OUT=a.exe
	CLEAN=del
	CLEAR=cls
endif

CC = g++
RUBIK := rubik/classes/*.cpp rubik/classes/auxiliares/*.cpp
BIBLIOTECAS := $(wildcard bibliotecas/*.o)
ALL := $(RUBIK) $(BIBLIOTECAS)

all: compile
	$(CC) main.cpp "rubik/rubik.o" "bibliotecas/variaveis-ambiente.o" -fopenmp -o $(OUT)
	$(CLEAR)
	./$(OUT)

test:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp rubik/scores/*.cpp -fopenmp -o $(OUT)

testO1:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp rubik/scores/*.cpp -fopenmp -o $(OUT) -O1

testO2:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp rubik/scores/*.cpp -fopenmp -o $(OUT) -O2

testO3:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp rubik/scores/*.cpp -fopenmp -o $(OUT) -O3

scramble:
	$(CC) scrambles/populate_scrambles.cpp rubik/*.cpp rubik/auxiliares/*.cpp -o populate.out
	./populate.out $(SEED) $(QUANTITY)
	
compile:
	$(CC) -c rubik/rubik.cpp -o rubik/rubik.o
	$(CC) -c bibliotecas/variaveis-ambiente.cpp -o bibliotecas/variaveis-ambiente.o

clean:
	$(CLEAN) rubik/*.o bibliotecas/*.o
	$(CLEAN) *.out *.bin *.exe
	$(CLEAR)