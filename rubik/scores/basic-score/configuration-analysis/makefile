all:
	g++ main.cpp ../../../auxiliares/*.cpp ../../../*.cpp ../../../scores/*.cpp ../../../scores/basic-score/*.cpp -o analysis.out -O3 -fopenmp

make tun:
	g++ tuning.cpp -O3 -o tuning.out
	
run-default:
	./analysis.out 3 2 2 1 0 3 2 1 0