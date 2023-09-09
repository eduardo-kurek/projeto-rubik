ifeq ($(TERM), xterm-256color)
	OUT=a.out
	CLEAN=rm
else
	OUT=a.exe
	CLEAN=del
endif

all:
	make compile
	gcc main.c "rubik/rubik.o" -o $(OUT)
	./$(OUT)

compile:
	gcc -c "rubik/rubik.c" -o "rubik/rubik.o"

test:
	make compile
	gcc testes.c "rubik/rubik.c" -o $(OUT)
	./$(OUT)

clean:
	$(CLEAN) *.out *.bin *.exe