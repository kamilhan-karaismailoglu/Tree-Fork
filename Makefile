CC = gcc

derle: ./TreeFork.c
	$(CC) ./TreeFork.c -o TreeFork 

calistir: ./TreeFork
	./TreeFork 2

valgrind: 
	valgrind --tool=memcheck --leak-check=full ./TreeFork 2

txtClean:
	rm *.txt

objCreate: ./TreeFork.c
	$(CC) -c ./TreeFork.c -o TreeFork.o

exeClean:
	rm -f TreeFork

objClean:
	rm -f TreeFork.o