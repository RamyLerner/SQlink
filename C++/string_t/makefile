CFLAGS  = -ansi -pedantic -g -Wall

go : string_t.o stringTest.o
	g++ -o go string_t.o stringTest.o

string_t.o : string_t.cpp string_t.h
	g++ -c $(CFLAGS) string_t.cpp

stringTest.o : stringTest.cpp string_t.h
	g++ -c $(CFLAGS) stringTest.cpp

