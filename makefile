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
	$(CC) main.cpp "rubik/rubik.o" "bibliotecas/variaveis-ambiente.o" -o $(OUT)
	$(CLEAR)
	./$(OUT)

test:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp -o $(OUT)

testO1:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp -o $(OUT) -O1

testO2:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp -o $(OUT) -O2

testO3:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp -o $(OUT) -O3

compile:
	$(CC) -c rubik/rubik.cpp -o rubik/rubik.o
	$(CC) -c bibliotecas/variaveis-ambiente.cpp -o bibliotecas/variaveis-ambiente.o

clean:
	$(CLEAN) rubik/*.o bibliotecas/*.o
	$(CLEAN) *.out *.bin *.exe
	$(CLEAR)