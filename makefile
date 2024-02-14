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
INCLUDES=$(ROOT)rubik/*.cpp $(ROOT)rubik/auxiliares/*.cpp $(ROOT)rubik/scores/*.cpp $(ROOT)managers/*.cpp $(ROOT)sqlite/*.o
LIBS=

all:
	$(CC) main.cpp $(INCLUDES) -o $(OUT)
	./$(OUT)
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

clean:
	$(CLEAN) rubik/*.o bibliotecas/*.o
	$(CLEAN) *.out *.bin *.exe
	$(CLEAR)