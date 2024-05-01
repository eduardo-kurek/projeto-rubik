ifeq ($(TERM), xterm-256color)
	CLEAN=rm
	CLEAR=clear
else
	CLEAN=del
	CLEAR=cls
endif

CXX := g++
CXXFLAGS := -O3 -Wall -std=c++17 -fopenmp

RUBIK_CPP := $(wildcard rubik/*.cpp)
AUX_CPP := $(wildcard rubik/auxiliares/*.cpp)
SCORES_CPP := $(wildcard rubik/scores/*.cpp)
BASIC_SCORE_CPP := $(wildcard rubik/scores/basic-score/*.cpp)

# Lista de arquivos .cpp
CPP_FILES := $(RUBIK_CPP) $(AUX_CPP) $(SCORES_CPP) $(BASIC_SCORE_CPP)
# Adicionando prefixo obj/ e trocando .cpp por .o
OBJ_FILES := $(addprefix obj/, $(CPP_FILES:.cpp=.o)) 

all: dir $(OBJ_FILES)

bin/%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJ_FILES)
dir:
	mkdir -p obj
	mkdir -p obj/rubik
	mkdir -p obj/rubik/auxiliares
	mkdir -p obj/rubik/scores
	mkdir -p obj/rubik/scores/basic-score
	mkdir -p bin

# make obj/test.o := g++ -c test.cpp -o obj/test.o
obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj
	rm -rf bin