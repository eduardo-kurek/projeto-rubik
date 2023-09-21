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
RUBIK := $(wildcard rubik/*.o)
BIBLIOTECAS := $(wildcard bibliotecas/*.o)
ALL := $(RUBIK) $(BIBLIOTECAS)

all: compile
	$(CC) main.cpp "rubik/rubik.o" "bibliotecas/variaveis-ambiente.o" -o $(OUT)
	$(CLEAR)
	./$(OUT)

test: compile
	$(CC) testes.c $(ALL) -o $(OUT)
	./$(OUT)

compile:
	$(CC) -c rubik/rubik.cpp -o rubik/rubik.o
	$(CC) -c bibliotecas/variaveis-ambiente.cpp -o bibliotecas/variaveis-ambiente.o

clean:
	$(CLEAN) rubik/*.o bibliotecas/*.o
	$(CLEAN) *.out *.bin *.exe
	$(CLEAR)