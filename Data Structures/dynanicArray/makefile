CFLAGS  = -ansi -pedantic -g -Wall 

dyArr : darray_int.o darray_main.o
	gcc -o dyArr darray_int.o darray_main.o

darray_int.o : darray_int.c darray_int.h
	gcc -c $(CFLAGS) darray_int.c

a2.o : darray_main.c darray_int.h
	gcc -c $(CFLAGS) darray_main.c