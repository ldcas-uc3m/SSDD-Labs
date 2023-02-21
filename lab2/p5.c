#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>


#define BUF_SIZE 256


char buffer[BUF_SIZE];
int  n_elementos = 0;  // elements in buffer

bool fin = false;  // signals end of file

// sync
pthread_mutex_t mutex;
pthread_mutex_t mutex_fin;
pthread_cond_t lleno;  // signals the buffer is full
pthread_cond_t vacio;  // signals the buffer is empty


void productor(int* f) {
	char c;
	int pos = 0;

	while (read(*f, &c, 1) > 0) {
		pthread_mutex_lock(&mutex);

		// if buffer is full, sleep (stop producing)
		while (n_elementos == BUF_SIZE) {
			pthread_cond_wait(&lleno, &mutex);
		}

		// produce
		buffer[pos] = c;
		pos = (pos + 1) % BUF_SIZE;
		n_elementos++;

		// if buffer has started to fill up again, wake up consumidor
		if (n_elementos == 1) {
			pthread_cond_signal(&vacio);
		}

		pthread_mutex_unlock(&mutex);
	}
	
	pthread_mutex_lock(&mutex_fin);
	
	fin = true;
	
	pthread_cond_signal(&vacio);
	pthread_mutex_unlock(&mutex_fin);
	
	pthread_exit(NULL);

}


void consumidor(int* f) {
	char c;
	int pos = 0;

	for (;;) {

		pthread_mutex_lock(&mutex);

		// if buffer is empty, sleep
		while (n_elementos == 0) {
			pthread_cond_wait(&vacio, &mutex);
		}
		
		// digest
		c = buffer[pos];
		pos = (pos + 1) % BUF_SIZE;
		n_elementos--;

		if (write(*f, &c, 1) < 0) {
			printf("Error de escritura \n");
			exit(0);
		}

		// if buffer has started to drain, wake up productor
		if (n_elementos == (BUF_SIZE - 1)) {
			pthread_cond_signal(&lleno);
		}

		pthread_mutex_lock(&mutex_fin);
		if (fin) {
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex_fin);

		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
	pthread_attr_t attr;
	pthread_t thid[2];

	int fe, fs;

	// check arguments
	if (argc < 3) {
		printf("Uso: %s  <fichero entrada> <fichero salida> \n", argv[0]);
		exit(0);
	}

	// open files
	fe = open (argv[1], O_RDONLY);
	if (fe < 0) {
		printf("Error al abrir %s\n", argv[1]);
		exit(0);
	}

	fs = creat (argv[2], 0700);
	if (fs < 0) {
		printf("Error al crear %s\n", argv[2]);
		close(fe);
		exit(0);
	}

	// init mutex and cond
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex_fin, NULL);
	pthread_cond_init(&lleno, NULL);
	pthread_cond_init(&vacio, NULL);


	// create threads
	pthread_attr_init(&attr);

	if (pthread_create(&thid[0], NULL, (void *) productor, &fe) == -1){
		printf("Error al crear el productor\n");
		exit(0);
	}

	if (pthread_create(&thid[1], NULL, (void *) consumidor, &fs) == -1){
		printf("Error al crear el consumidor\n");
		exit(0);
	}

	pthread_join(thid[0], NULL);
	pthread_join(thid[1], NULL);
	
	// cleanup
	pthread_cond_destroy(&lleno);
	pthread_cond_destroy(&vacio);
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutex_fin);
	
	close(fe);
	close(fs);

	exit(0);

}
	

	

