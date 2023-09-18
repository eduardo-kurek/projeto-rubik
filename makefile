ifeq ($(TERM), xterm-256color)
	OUT=a.out
	CLEAN=rm
	CLEAR=clear
else
	OUT=a.exe
	CLEAN=del
	CLEAR=cls
endif

RUBIK := $(wildcard rubik/*.o)
BIBLIOTECAS := $(wildcard bibliotecas/*.o)
ALL := $(RUBIK) $(BIBLIOTECAS)

all: compile
	gcc main.c "rubik/*.o" "bibliotecas/*.o" -o $(OUT)
	$(CLEAR)
	./$(OUT)

test: compile
	gcc testes.c $(ALL) -o $(OUT)
	./$(OUT)

compile:
	gcc -c rubik/rubik.c -o rubik/rubik.o
	gcc -c bibliotecas/variaveis-ambiente.c -o bibliotecas/variaveis-ambiente.o

clean:
	$(CLEAN) rubik/*.o bibliotecas/*.o
	$(CLEAN) *.out *.bin *.exe
	$(CLEAR)