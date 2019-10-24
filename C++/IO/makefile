CFLAGS  = -ansi -pedantic -g -Wall

go : virtio_t.o asciiio_t.o binio_t.o IOtest.o
	g++ -o go virtio_t.o asciiio_t.o binio_t.o IOtest.o

virtio_t.o : virtio_t.cpp virtio_t.h
	g++ -c $(CFLAGS) virtio_t.cpp

asciiio_t.o : asciiio_t.cpp asciiio_t.h
	g++ -c $(CFLAGS) asciiio_t.cpp

binio_t.o : binio_t.cpp binio_t.h
	g++ -c $(CFLAGS) binio_t.cpp

IOtest.o : IOtest.cpp binio_t.h asciiio_t.h virtio_t.h
	g++ -c $(CFLAGS) IOtest.cpp

