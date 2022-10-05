#include "server.h"
#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>


int main()
{
    char server_message[256] = "You have reacher the server.";

    // create socket file descriptor, using IPV4, TCP, and IP
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Failed to create socket file descriptor");
        exit(EXIT_FAILURE);
    }

    // set socket options (helps in reuse of address and port)
    /* int socket_options = setsockopt(); */

    // specify server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind socket to server address
    int bind_socket = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    if (bind_socket == -1)
    {
        perror("Failed to bind socket to server address");
        exit(EXIT_FAILURE);
    }


    // listen client to approach the server to make a connection
    int listen_success = listen(server_socket, 9);
    if (listen_success == -1)
    {
        perror("Error listening for connection");
        exit(EXIT_FAILURE);
    }

    // accept connection
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1)
    {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    // send message to client
    send(client_socket, server_message, sizeof(server_message), 0);

    // closing the connected socket
    close(client_socket);

    // closing the listening socket
    shutdown(server_socket, SHUT_RDWR);


    return 0;


}
