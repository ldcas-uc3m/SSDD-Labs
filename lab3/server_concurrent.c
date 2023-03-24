/*
Servidor de echo concurrente con sockets TCP
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "lines.h"


// sync
pthread_mutex_t mutex_sd;  // mutex for sd
pthread_cond_t c_sd;  // variable condicional de bloqueo
bool copied = false;  // variable condicional de control
pthread_mutex_t mutex_stdout;  // mutex for stdout



void* treat_petition(int* sd) {

    char buff[MAX_LINE];
    // unsigned long int tid = (unsigned long int) pthread_self();

    // copy sd
    pthread_mutex_lock(&mutex_sd);

    int local_sd = *sd;

    copied = true;
    pthread_cond_signal(&c_sd);
    pthread_mutex_unlock(&mutex_sd);

    while (true) {
        // read lines
        readLine(local_sd, buff, MAX_LINE);
        if (strcmp(buff, "EXIT\0") == 0) {
            printf("Client %i disconnected\n", local_sd);
            break;
        }
        printf("Client %i: %s\n", local_sd, buff);

        // echo
        sendMessage(local_sd, buff, strlen(buff) + 1);
    }

    close(local_sd);

    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
	int sd, newsd;
    socklen_t size;
    struct sockaddr_in server_addr, client_addr;

    // arguments
    if (argc != 2) {
        printf("Usage: %s <serverPort>\n", argv[0]);
        exit(0);
    }

    // threads
    pthread_attr_t t_attr;
    pthread_t thid;

    // init mutex and conditions
    pthread_cond_init(&c_sd, NULL);
	pthread_mutex_init(&mutex_sd, NULL);

    pthread_mutex_init(&mutex_stdout, NULL);

	pthread_attr_init(&t_attr);
    pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);

    
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
    listen(sd, SOMAXCONN);  // open socket

    while (true) {
        // accept petition
        newsd = accept(sd, (struct sockaddr*) &client_addr, &size);
        if (newsd < 0) {
            perror("Error in accept\n");
            return -1;
        }
        printf("Client %i connected", newsd);

        // create thread
        if (pthread_create(&thid, &t_attr, (void*) treat_petition, (void*) &newsd) == 0) {  // wait to copy petition
            // mutex logic
            pthread_mutex_lock(&mutex_sd);

            while (!copied) {  // wait for thread to copy newsd
                pthread_cond_wait(&c_sd, &mutex_sd);
            }

            copied = false;  // reset variable
            pthread_mutex_unlock(&mutex_sd);

        } else {
            perror("Error al crear el thread\n");
            return -1;
        }

    }

    close (sd);
    return(0);
}

