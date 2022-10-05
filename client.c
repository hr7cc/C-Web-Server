#include "server.h"

int main()
{
    char* message = "Message from client\n";

    // create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify socket address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // check connection status
    int connect_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_status == -1)
    {
        perror("Error making connection");
        exit(EXIT_FAILURE);
    }

    // receive data from server
    char server_response[256];
    recv(client_socket, &server_response, sizeof(server_response), 0);

    // print data from server
    printf("\n%s\n", server_response);

    // send data to server
    send(client_socket, message, strlen(message), 0);

    // close socket
    close(client_socket);


    return 0;
}
