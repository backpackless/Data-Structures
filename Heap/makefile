CC = gcc
CFLAGS = -std=c90 -pedantic -Wall -Werror -c

a.out: myProgram.o
	$(CC) myProgram.o HeapImplementation.o StudentImplementation.o 

myProgram.o: myProgram.c HeapImplementation.o StudentImplementation.o 
	$(CC) $(CFLAGS) myProgram.c 

HeapImplementation.o: HeapImplementation.c HeapInterface.h HeapType.h
	$(CC) $(CFLAGS) HeapImplementation.c 

StudentImplementation.o: StudentImplementation.c StudentInterface.h StudentType.h
	$(CC) $(CFLAGS) StudentImplementation.c 

clean:
	rm *.o *.out


