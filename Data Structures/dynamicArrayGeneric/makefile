CFLAGS  = -ansi -pedantic -g -Wall -lm

genArr : darray_generic.o darray_main.o point.o
	gcc -o genArr darray_generic.o darray_main.o

darray_generic.o : darray_generic.c darray_generic.h
	gcc -c $(CFLAGS) darray_generic.c

point.o : point.c point.h
	gcc -c $(CFGLAGS) point.c

darray_main.o : darray_generic.h point.h darray_main.c
	gcc -c $(CFLAGS) darray_main.c