CFLAGS  = -ansi -pedantic -g -Wall

go : tException_t.o tExceptionTest.o
	g++ -o go tException_t.o tExceptionTest.o

tException_t.o : tException_t.cpp tException_t.h
	g++ -c $(CFLAGS) tException_t.cpp

tExceptionTest.o : tExceptionTest.cpp tException_t.h
	g++ -c $(CFLAGS) tExceptionTest.cpp
