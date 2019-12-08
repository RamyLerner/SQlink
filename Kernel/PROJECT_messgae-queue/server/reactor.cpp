#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "server_epoll.h"

const int Reactor::max_events = 10;
const int Reactor::port = 8080;

static const int Connection_fd_handler::max_fd = 10;
static const int Connection_fd_handler::max_buff = 4096;

static void ERR(int errcode, const char *msg)
{
    if (errcode == -1)
    {
        perror(NULL);
        fprintf(stderr, "%s\n", msg);
        exit(1);
    }
}

int Reactor::socket_init()
{
    int socket_fd;
    ERR(socket_fd = socket(AF_INET, SOCK_STREAM, 0), "Failed creating socket()");
    struct sockaddr_in serv_addr;
    bzero((void *)serv_addr, sizeof(struct sockaddr_in));
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr->sin_port = htons(port);
    ERR(bind(socket_fd, (struct sockaddr *)serv_addr, sizeof(*serv_addr)), "Failed bind()");
    ERR(listen(socket_fd, 5), "Failed listen()");
    return socket_fd;

    socklen_t len;
    struct sockaddr_in servaddr, cli;

    /* socket create and verification */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    err(sockfd);
    printf("Socket successfully created..\n");

    int optval = 1;
    err(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)));

    /* assign IP, port */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    /* Binding newly created socket to given IP and verification */
    err(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)));
    printf("Socket successfully binded..\n");

    /* Now server is ready to listen and verification */
    err(listen(sockfd, 5));
    printf("Server listening..\n");
    len = sizeof(cli);

    int epollfd = epoll_create1(0);
    err(epollfd);

    struct epoll_event event;
    event.data.fd = sockfd;
    event.events = EPOLLIN;
    err(epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &event));
}

void Reactor::loop()
{
    while (1)
    {
        struct epoll_event all_events[Reactor::max_events];
        int num_events = epoll_wait(epoll_fd, all_events, Reactor::max_events, -1);
        ERR(num_events, "Failed at epoll_wait");
        for (int i = 0; i < num_events; i++)
        {
            if (ready_events[i].events == EPOLLIN)
            {
                handler_map[reay_events[i].fd].handle_in(epoll_fd);
            }
            if (ready_events[i].events == EPOLLOUTOUT)
            {
                handler_map[reay_events[i].fd].handle_out(epoll_fd);
            }
        }
    }
}

void Socket_fd_handler::handle_in(int epollfd)
{
    struct sockaddr_in servaddr, cli;
    int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
    err(connfd);
    printf("server acccept the client...\n");
    struct epoll_event event;
    event.data.fd = connfd;
    event.events = EPOLLIN;
    err(epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event));
}

void Connection_fd_handler::handle_in(int epollfd)
{
    ssize_t bytes_read = read(fd, read_buffers[fd] + count_read[fd], max_buff);
    count_read[fd] += bytes_read;
    if (has_message_ended(read_buffers[fd], count_read[fd]))
    {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = EPOLLOUT;
        err(epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event));
        buffers_to_write[fd] = response;
        count_to_write[fd] = strlen(response);
    }
}

void Connection_fd_handler::handle_out(int epollfd)
{
    ssize_t bytes_written = write(fd, buffers_to_write[fd], count_to_write[fd]);
    err(bytes_written);
    buffers_to_write[fd] += bytes_written;
    count_to_write[fd] -= bytes_written;
    if (count_to_write[fd] == 0)
    {
        struct epoll_event event;
        event.data.fd = fd;
        err(epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event));
        err(close(fd));
    }
}

int has_message_ended(char *buffer, int offset)
{
    if (offset < 4)
    {
        return 0;
    }
    else
    {
        return memcmp("\r\n\r\n", buffer + (offset - 4), 4) == 0;
    }
}

int main(){

}