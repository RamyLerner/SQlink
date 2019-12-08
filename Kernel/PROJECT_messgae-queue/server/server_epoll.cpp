
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>

const int max_events = 10;
const int max_buff = 4096;
const int port = 8080;

/*const int max_fds = 10;*/
#define max_fds 10
const char *buffers_to_write[max_fds];
int count_to_write[max_fds];
const char *buffers_to_read[max_fds];

const char *response =
    "HTTP/1.1 200 OK\n"
    "\n"
    "<html>"
    "<body>"
    "<h1>Welcome to my website</h1>"
    "<p>my website is bla bla bla</p>"
    "</body>"
    "</html>";

void func(int connectionfd)
{
    char buff[max_buff];
    int ret = read(connectionfd, buff, sizeof(buff));

    printf("Data I got from client follows...\n");
    buff[ret] = 0;
    printf("%s", buff);
    ret = write(connectionfd, response, strlen(response));
    printf("responding ret is %d, strlen is %ld\n", ret, strlen(response));
    close(connectionfd);
}

void err(int val)
{
    if (val == -1)
    {
        perror(NULL);
        exit(EXIT_FAILURE);
    }
}

int main()
{
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

    while (1)
    {
        struct epoll_event all_events[max_events];
        int num_events = epoll_wait(epollfd, all_events, max_events, -1);
        err(num_events);
        for (int i = 0; i < num_events; i++)
        {
            int fd = all_events[i].data.fd;
            int events = all_events[i].events;
            if (fd == sockfd)
            {
                int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
                err(connfd);
                printf("server acccept the client...\n");
                struct epoll_event event;
                event.data.fd = connfd;
                event.events = EPOLLIN;
                err(epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event));
            }
            else
            {
                if (events & EPOLLIN)
                {
                    char buf[4096];
                    ssize_t bytes_read = read(fd, buf, 4096);
                    buf[bytes_read] = '\0';
                    printf("buf is %s\n", buf);
                    printf("bytes_read is %ld\n", bytes_read);
                    /*if (buf[bytes_read - 1] == '\n' && buf[bytes_read - 2] == '\n')
                    {*/
                        struct epoll_event event;
                        event.data.fd = fd;
                        event.events = EPOLLOUT;
                        err(epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event));
                        buffers_to_write[fd] = response;
                        count_to_write[fd] = strlen(response);
                    /*}*/
                }
                if (events & EPOLLOUT)
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
            }
        }
    }
    err(close(sockfd));
    err(close(epollfd));
    return EXIT_SUCCESS;
}
