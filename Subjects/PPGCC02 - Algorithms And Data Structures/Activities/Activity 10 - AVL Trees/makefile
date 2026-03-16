all: arvore

arvore:
	clear
	gcc -c arvore_avl.c
	gcc main.c arvore_avl.o -o main
	./main
	make clean

clean:
	rm -f *.o main
