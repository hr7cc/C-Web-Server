#include "server.h"

int main()
{
    // create socket
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify address for socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // check conneciton status
    int connect_status = connect(tcp_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_status == -1)
    {
        printf("Error making connection\n");
    }

    // receive data from server
    char server_response[256];
    recv(tcp_socket, &server_response, sizeof(server_response), 0);

    printf("Data received: %s\n", server_response);

    // close socket
    close(tcp_socket);


    return 0;
}
