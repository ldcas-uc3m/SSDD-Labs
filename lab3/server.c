#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lines.h"


int main(int argc, char* argv[]) {
	int sd, newsd;
    socklen_t size;
    struct sockaddr_in server_addr, client_addr;

    if (argc != 2) {
        printf("Usage: server <serverPort>\n");
        exit(0);
    }

    // configure socket
    if ((sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("Error in socket");
        exit(1);
    }

    int val = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char*) &val, sizeof(int)) < 0) {
        perror("Error in option");
        exit(1);
    }
    
    bzero((char*) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;


    // bind
    if (bind(sd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Error in bind\n");
        return -1;
    }

    // main loop
    char buff[MAX_LINE];

    listen(sd, SOMAXCONN);  // open socket

    while (true) {
        // accept petition
        newsd = accept(sd, (struct sockaddr*) &client_addr, &size);
        if (newsd < 0) {
            perror("Error in accept\n");
            return -1;
        }

        while (true) {
            // read lines
            readLine(newsd, buff, MAX_LINE);
            if (strcmp(buff, "EXIT") == 0) break;
            printf("%s\n", buff);

            // echo
            sendMessage(newsd, buff, strlen(buff) + 1);

        }

        close(newsd);
    }


    close (sd);
    return(0);
}

