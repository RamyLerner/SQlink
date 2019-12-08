CFLAGS=-O2 -pedantic -Wall -Werror

.PHONY: all 
all: server_epoll server_thread

server_epoll : server_epoll.c
	gcc $(CFLAGS) -o $@ $<

server_thread : server_thread.c 
	gcc $(CFLAGS) -o $@ $< -pthread

.PHONY: clean
clean:
	rm -f server_epoll server_thread
