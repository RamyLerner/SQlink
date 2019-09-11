CFLAGS  = -ansi -pedantic -g

prog : producers.o consumers.o wQueue.o prodCons.o
	gcc -o prog producers.o consumers.o wQueue.o prodCons.o -pthread

prodCons.o : prodCons.c producers.h consumers.h wQueue.h
	gcc -c $(CFLAGS) prodCons.c

producers.o : producers.c producers.h wQueue.h
	gcc -c $(CFLAGS) producers.c

consumers.o : consumers.c consumers.h wQueue.h
	gcc -c $(CFLAGS) consumers.c

wQueue.o : wQueue.c wQueue.h
	gcc -c $(CFLAGS) wQueue.c

