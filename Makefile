all: main.o
	gcc main.o -lev3dev-c -o bin/main

main.o: main.c
	gcc -c main.c -I. 

clean:
	rm -f *.o
	rm -f bin/*
