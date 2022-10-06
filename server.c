#include "defs.h"
#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

char* readhtml(char* page)
{
    int n = 1;
    char *str = (char *) malloc(n);
    FILE *ptr = fopen(page, "r");
    char ch[1];
    do {
        n++;
        ch[0] = fgetc(ptr);
        str = realloc(str, n);
        strncat(str, ch, 1);
    } while (ch[0] != EOF);
    return str;
}

int main()
{
    char full_response[1024];
    char line1[] = "HTTP/1.1 200 OK\n";
    char line2[] = "Content-Type: text/html\n";
    char line3[] = "Content-Length: 9000\n";

    /* parse_http(); */

    char *str = readhtml("index.html");

    int full_response_length = strlen(line1) + strlen(line2) +strlen(line3) + strlen(str);

    strcat(full_response, line1);
    strcat(full_response, line2);
    strcat(full_response, line3);
    strcat(full_response, str);

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
        send(client_socket, full_response, full_response_length-1, 0);

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

    free(str);

    return 0;
}
