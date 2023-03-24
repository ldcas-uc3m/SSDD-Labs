#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "lines.h"


int main(int argc, char *argv[]) {

    int sd;
    struct sockaddr_in server_addr;
    struct hostent *hp;

    if (argc != 3) {
        printf("Usage: client <serverAddress> <serverPort>\n");
        exit(0);
    }

	// the socket is created
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd < 0) {
        perror("Error in socket");
        exit(1);
    }

	// Obtain Server address 
    bzero((char*) &server_addr, sizeof(server_addr));
    hp = gethostbyname(argv[1]);
    if (hp == NULL) {
        perror("Error en gethostbyname");
        exit(1);
    }

	memcpy(&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));

	// establish the connection
    if (connect(sd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Error en la conexión\n");
        return -1;
    }

    printf("Connected to %s port %s\n", argv[1], argv[2]);

    char buff[MAX_LINE];

    // main loop
    while (true) {
        readLine(STDIN_FILENO, buff, MAX_LINE);
        sendMessage(sd, buff, strlen(buff) + 1);
        
        if (strcmp(buff, "EXIT") == 0) break;

        // print echo
        listen(sd, SOMAXCONN);  // listen on socket

        readLine(sd, buff, MAX_LINE);
        printf("Server: %s\n", buff);
        
    }

    close (sd);

    return(0);
}

