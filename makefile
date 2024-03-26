ifeq ($(TERM), xterm-256color)
	OUT=a.out
	CLEAN=rm
	CLEAR=clear
else
	OUT=a.exe
	CLEAN=del
	CLEAR=cls
endif

CC=g++
ROOT=
AUXILIARES = $(filter-out $(ROOT)rubik/auxiliares/StickerCoord.cpp, $(wildcard $(ROOT)rubik/auxiliares/*.cpp))
INCLUDES=$(ROOT)rubik/*.cpp $(ROOT)rubik/auxiliares/StickerCoord.cpp $(AUXILIARES) $(ROOT)rubik/scores/*.cpp $(ROOT)rubik/scores/basic-score/*.cpp
LIBS=

CC=g++
ROOT=
TARGET=app
CPP_FILES := $(wildcard $(ROOT)rubik/*.cpp) $(wildcard $(ROOT)rubik/auxiliares/*.cpp) $(wildcard $(ROOT)rubik/scores/**.cpp)
OBJ_FILES := $(addprefix obj/,$(CPP_FILES:$(ROOT)rubik/%.cpp=%.o))
CFLAGS		:= -O3 -Wall -std=c++17 	-fopenmp $(AFLAGS)
LFLAGS = -lm $(AFLAGS)
EXE = bin/$(TARGET)

all: DIR $(EXE)

print:
	@echo "CPP_FILES: $(CPP_FILES)"
	@echo " "
	@echo "OBJ_FILES: $(OBJ_FILES)"

DIR:
	mkdir -p obj
	mkdir -p obj/auxiliares
	mkdir -p obj/scores
	mkdir -p obj/scores/basic-score
	mkdir -p bin

$(EXE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^  $(LFLAGS) 

obj/%.o: rubik/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf bin
	rm -rf obj

test:
	$(CC) test.cpp $(INCLUDES) $(LIBS) -o $(OUT)

testO1:
	$(CC) test.cpp $(INCLUDES) -o $(OUT) -O1

testO2:
	$(CC) test.cpp $(INCLUDES) -o $(OUT) -O2

testO3:
	$(CC) test.cpp $(INCLUDES) -o $(OUT) -O3

scramble:
	$(CC) scrambles/populate_scrambles.cpp rubik/*.cpp rubik/auxiliares/*.cpp -o populate.out
	./populate.out $(SEED) $(QUANTITY)
