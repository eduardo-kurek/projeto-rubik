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
SQLITE=sqlite/*.o
INCLUDES=$(ROOT)rubik/*.cpp $(ROOT)rubik/auxiliares/*.cpp $(ROOT)rubik/scores/*.cpp $(ROOT)managers/*.cpp $(ROOT)$(SQLITE)
LIBS=

<<<<<<< HEAD
all: compile
	$(CC) main.cpp "rubik/rubik.o" "bibliotecas/variaveis-ambiente.o" -fopenmp -o $(OUT)
	$(CLEAR)
=======
all:
	$(CC) main.cpp $(INCLUDES) -o $(OUT)
>>>>>>> score
	./$(OUT)
test:
<<<<<<< HEAD
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp rubik/scores/*.cpp -fopenmp -o $(OUT)

testO1:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp rubik/scores/*.cpp -fopenmp -o $(OUT) -O1

testO2:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp rubik/scores/*.cpp -fopenmp -o $(OUT) -O2

testO3:
	$(CC) test.cpp rubik/*.cpp rubik/auxiliares/*.cpp rubik/scores/*.cpp -fopenmp -o $(OUT) -O3
=======
	$(CC) test.cpp $(INCLUDES) $(LIBS) -o $(OUT)

testO1:
	$(CC) test.cpp $(INCLUDES) -o $(OUT) -O1

testO2:
	$(CC) test.cpp $(INCLUDES) -o $(OUT) -O2

testO3:
	$(CC) test.cpp $(INCLUDES) -o $(OUT) -O3
>>>>>>> score

scramble:
	$(CC) scrambles/populate_scrambles.cpp rubik/*.cpp rubik/auxiliares/*.cpp -o populate.out
	./populate.out $(SEED) $(QUANTITY)

clean:
	$(CLEAN) rubik/*.o bibliotecas/*.o
	$(CLEAN) *.out *.bin *.exe
	$(CLEAR)