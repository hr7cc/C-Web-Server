
#ifndef server_h
#define server_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

struct Server {
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    void (*launch)(void);
};

struct Server server_constructor(
    int domain,
    int service,
    int protocol,
    u_long interface,
    int port,
    int backlog,

    struct sockaddr_in_address;

    int sckt;
    void (*launch)(void);

};

    struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void(*launch)(void));



#endif
