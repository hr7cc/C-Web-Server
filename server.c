#include "server.h"
#include <asm-generic/socket.h>
#include <sys/socket.h>

int PORTNUM = 8080;

int main()
{
    char server_message[256] = "You have reacher the server.";

    // create socket file descriptor, using IPV4, TCP, and IP
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // set socket options (helps in reuse of address and port)
    /* int socket_options = setsockopt(); */

    // specify server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORTNUM);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind server
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));


    // listen
    listen(server_socket, 9);

    int client_socket = accept(server_socket, NULL, NULL);

    // send message
    send(client_socket, server_message, sizeof(server_message), 0);

    // close socket
    close(server_socket);


    return 0;


}
