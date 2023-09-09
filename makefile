compile:
	gcc -c "rubik/rubik.c" -o "rubik/rubik.o"
	gcc -c "rubik/branch.c" -o "rubik/branch.o"

all:
	make compile
	gcc main.c "rubik/rubik.o" -o a.bin
	./a.bin

nc:
	make compile
	gcc main.c "rubik/rubik.o"
	./a.bin

test:
	make compile
	gcc testes.c "rubik/rubik.c" "rubik/branch.c" -o a.bin
	./a.bin