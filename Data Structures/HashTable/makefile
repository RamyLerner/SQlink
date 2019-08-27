CFLAGS  = -ansi -pedantic -g -Wall

hsTest :  hashTable.o linkedList.o hashTest.o
	gcc -o hsTest hashTable.o linkedList.o hashTest.o

hashTable.o : hashTable.c hashTable.h linkedList.h destroyFunc.h
	gcc -c $(CFLAGS) hashTable.c

linkedList.o : linkedList.c linkedList.h destroyFunc.h
	gcc -c $(CFGLAGS) linkedList.c

hashTest.o : hashTest.c hashTable.h destroyFunc.h linkedList.h
	gcc -c $(CFLAGS) hashTest.c