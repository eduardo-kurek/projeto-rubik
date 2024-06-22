ifeq ($(TERM), xterm-256color)
	CLEAN=rm
	CLEAR=clear
else
	CLEAN=del
	CLEAR=cls
endif

CXX := g++
CXXFLAGS := -O3 -std=c++20 -fopenmp

RUBIK_CPP := $(wildcard rubik/*.cpp)
AUX_CPP := $(wildcard rubik/auxiliares/*.cpp)
# Descomentar a linha abaixo caso estiver no LINUX
# AUX_CPP := rubik/auxiliares/StickerCoord.cpp $(filter-out rubik/auxiliares/StickerCoord.cpp, $(AUX_CPP))
SCORES_CPP := $(wildcard rubik/scores/*.cpp)
BASIC_SCORE_CPP := $(wildcard rubik/scores/basic-score/*.cpp)
SOLVERS_CPP := $(wildcard rubik/solvers/*.cpp)
SERVICES_CPP := $(wildcard services/*.cpp)

# Arquivos de tuning do BasicScore
BS_TUNING := $(wildcard tuning/basic-score/*.cpp) $(wildcard tuning/scrambles/*.cpp)
BS_TUNING_BIN := $(addprefix bin/, $(BS_TUNING:.cpp=)) 

# Lista de arquivos .cpp
CPP_FILES := $(RUBIK_CPP) $(AUX_CPP) $(SCORES_CPP) $(BASIC_SCORE_CPP) $(SOLVERS_CPP) $(SERVICES_CPP)
# Adicionando prefixo obj/ e trocando .cpp por .o
OBJ_FILES := $(addprefix obj/, $(CPP_FILES:.cpp=.o)) 

all: dir $(OBJ_FILES) $(BS_TUNING_BIN)
	./bin/tuning/scrambles/generator 37 100
	make bin/test

reset:
	make clean
	make
	make bin/test

bin/%: %.cpp $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJ_FILES)
dir:
	mkdir -p obj
	mkdir -p obj/rubik
	mkdir -p obj/rubik/auxiliares
	mkdir -p obj/rubik/scores
	mkdir -p obj/rubik/solvers
	mkdir -p obj/rubik/scores/basic-score
	mkdir -p obj/services
	mkdir -p bin
	mkdir -p bin/tuning
	mkdir -p bin/tuning/basic-score
	mkdir -p bin/tuning/scrambles

# make obj/test.o := g++ -c test.cpp -o obj/test.o
obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj
	rm -rf bin
	rm -f tuning/scrambles/*.scr