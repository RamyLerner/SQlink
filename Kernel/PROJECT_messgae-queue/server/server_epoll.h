#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <map>

class Reactor
{
public:
    Reactor()
    {
        socket_init();
        epoll_init();
    }

    void loop();

private:
    int socket_fd;
    int epoll_fd;
    std::map<int, Fd_handler*> handler_map;
    static const int max_events;
    static const int port;

    int epoll_init();
    int socket_init();
    
}


class Fd_handler
{
public:
    virtual void handle_in();
    virtual void handle_out();

private:
};


class Connection_fd_handler : public Fd_handler
{
public:
    Connection_fd_handler(int fd) : connection_fd(fd) {
        read_buffers[fd] = new char[max_buff];
    }
    void handle_in(int epollfd);
    void handle_out(int epollfd);
    static const int max_fd;
    static const int max_buff;
private:
    int connection_fd;
    char *buffers_to_write[Reactor::max_fds];
    int count_to_write;
    const char *read_buffers[Reactor::max_fds];
    int count_read[Reactor::max_fds];
    int has_message_ended(char *message, int bytes_read);
};


class Socket_fd_handler : public Fd_handler
{
public:
    Socket_fd_handler(int fd) : socket_fd(fd){}
    void handle_in(int epollfd);
private:
    int socket_fd;
};