all: arvore

arvore:
	clear
	gcc -c arvore_binaria.c
	gcc main.c arvore_binaria.o -o main
	./main
	make clean

clean:
	rm -f *.o main
