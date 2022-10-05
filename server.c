#include "server.h"
#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void parse_http(char* request)
{

    /* Find out where everything is */
    const char *start_of_path = strchr(request, ' ') + 1;
    const char *start_of_query = strchr(start_of_path, '?');
    const char *end_of_query = strchr(start_of_query, ' ');

    /* Get the right amount of memory */
    char path[start_of_query - start_of_path];
    char query[end_of_query - start_of_query];

    /* Copy the strings into our memory */
    strncpy(path, start_of_path,  start_of_query - start_of_path);
    strncpy(query, start_of_query, end_of_query - start_of_query);

    /* Null terminators (because strncpy does not provide them) */
    path[sizeof(path)] = 0;
    query[sizeof(query)] = 0;

    /*Print */
    printf("%s\n", query);
    printf("%s\n", path);

};

int main()
{
    char server_message[1024] = "You have reacher the server.";
    /* char server_message[1024] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!"; */
    /* char server_message[1024] = "GET /index.html HTTP/1.1\nHost: 127.0.0.1:9001\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:103.0) Gecko/20100101 Firefox/103.0\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*\/\*;q=0.8\nAccept-Language: en-GB,en;q=0.5\nAccept\n"; */

    /* parse_http(server_message); */





    // create socket file descriptor, using IPV4, TCP, and IP
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Failed to create socket file descriptor");
        exit(EXIT_FAILURE);
    }

    // set socket options (helps reuse of address and port)
    int opt = 1;
    int set_options = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (set_options == -1)
    {
        perror("Failed to set socket options");
        exit(EXIT_FAILURE);
    }

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

    while(1)
    {
        // accept connection
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1)
        {
            perror("Error accepting connection");
            exit(EXIT_FAILURE);
        }

        // send message to client
        send(client_socket, server_message, sizeof(server_message), 0);

        // recieve message from client
        char server_response[1024];
        recv(client_socket, &server_response, sizeof(server_response), 0);

        // print message from client
        printf("\n%s\n", server_response);


        // closing the connected socket
        close(client_socket);
    }

    // closing the listening socket
    shutdown(server_socket, SHUT_RDWR);


    return 0;


}
