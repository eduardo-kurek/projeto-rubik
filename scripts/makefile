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
SQLITE=sqlite/*.o
INCLUDES=$(ROOT)rubik/*.cpp $(ROOT)rubik/auxiliares/*.cpp $(ROOT)rubik/scores/*.cpp $(ROOT)managers/*.cpp $(ROOT)$(SQLITE)
LIBS=-fopenmp

# SCRIPT PARA POPULAR O BANCO DE DADOS COM EMBARALHAMENTOS
# CRIA TABELAS DE scramble_1 ATÉ scramble_20, UMA UNICA COLUNA CHAMADA scramble
# USO: make populate-scrambles SEED=1 QUANT=1000
# SEED: semente para o gerador de números aleatórios
# QUANT: quantidade de embaralhamentos a serem gerados por tabela
populate-scrambles:
	$(CC) scrambles.cpp $(INCLUDES) $(LIBS) -o $(OUT)
	./$(OUT) $(SEED) $(QUANT)
	$(CLEAN) $(OUT)