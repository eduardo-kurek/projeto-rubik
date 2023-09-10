ifeq ($(TERM), xterm-256color)
	OUT=a.out
	CLEAN=rm
	CLEAR=clear
else
	OUT=a.exe
	CLEAN=del
	CLEAR=cls
endif

all:
	make compile
	gcc main.c "rubik/rubik.o" -o $(OUT)
	$(CLEAR)
	./$(OUT)

compile:
	gcc -c "rubik/rubik.c" -o "rubik/rubik.o"

test:
	make compile
	gcc testes.c "rubik/rubik.c" -o $(OUT)
	$(CLEAR)
	./$(OUT)

clean:
	$(CLEAN) *.out *.bin *.exe
	$(CLEAR)