CFLAGS  = -ansi -pedantic -g -Wall

go : memManager_t.o memPage_t.o memPool_t.o memTest.o
	g++ -o go memManager_t.o memPage_t.o memPool_t.o memTest.o

memManager_t.o : memManager_t.cpp memManager_t.h
	g++ -c $(CFLAGS) memManager_t.cpp

memPage_t.o : memPage_t.cpp memPage_t.h memManager_t.h
	g++ -c $(CFLAGS) memPage_t.cpp

memPool_t.o : memPool_t.cpp memPool_t.h memPage_t.h memManager_t.h
	g++ -c $(CFLAGS) memPool_t.cpp

memTest.o : memTest.cpp memPool_t.h memPage_t.h memManager_t.h
	g++ -c $(CFLAGS) memTest.cpp

