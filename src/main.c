#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8181
#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *ip = "127.0.0.1";
    char *hello = "Hello, Server!!!";    
    char buffer[BUFFER_SIZE] = {0};

    if(argc == 2)
    {
        ip = argv[1];
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent to %s\n",ip);
    
    int valread;
    do{
        valread = read(sock, buffer, BUFFER_SIZE);
    }while (valread == 0);
    if(valread > 0)
    {
      printf("Received ack: %s\n", buffer);        
    }

    close(sock);
    return 0;
}
