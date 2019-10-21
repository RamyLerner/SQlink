CFLAGS  = -ansi -pedantic -g -Wall

go : meeting_t.o day_t.o calendarTest.o
	g++ -o go meeting_t.o day_t.o calendarTest.o

meeting_t.o : meeting_t.cpp meeting_t.h
	g++ -c $(CFLAGS) meeting_t.cpp

day_t.o : day_t.cpp day_t.h meeting_t.h
	g++ -c $(CFLAGS) day_t.cpp

calendarTest.o : calendarTest.cpp meeting_t.h day_t.h
	g++ -c $(CFLAGS) calendarTest.cpp