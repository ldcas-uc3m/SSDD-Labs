#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_THREADS	 2
#define ITER 		10

// sync
pthread_cond_t c;  // variable condicional de bloqueo
bool copiado = false;  // variable condicional de control
pthread_mutex_t mutex;


void funcion(int *id) {
	int s;
	double k;
	int mid = *id;  // cada thread recibe un número (0 o 1)

	// mutex logic
	pthread_mutex_lock(&mutex);
	copiado = true;  // update conditional variable
	pthread_cond_signal(&c);  // signal all sleeping threads
	pthread_mutex_unlock(&mutex);

	for (unsigned int j = 0 ; j < ITER; j++) {
		k = (double) rand_r((unsigned int *) &s) / RAND_MAX;	
		usleep((int) (k * 100000)); // duerme entre 0 y 100 ms
		printf("Ejecuta el thread %d iteracion %d \n", mid, j);
	}
	
	pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
	unsigned int j;
	pthread_attr_t attr;
	pthread_t thid[NUM_THREADS];
	struct timeval t;

	gettimeofday(&t, NULL);
	srand(t.tv_sec);	// se inicializa la semilla de no. pseudoaleatorios

	// init mutex and cond
	pthread_cond_init(&c, NULL);
	pthread_mutex_init(&mutex, NULL);

	pthread_attr_init(&attr);

	for (j = 0; j < NUM_THREADS; j++) {
		if (pthread_create(&thid[j], NULL, (void *) funcion, &j) == -1){
			printf("Error al crear los threads\n");
			exit(0);
		}

		// mutex logic
		pthread_mutex_lock(&mutex);  // lock

		while (!copiado) {  // wait for thread to copy id
			pthread_cond_wait(&c, &mutex);  // sleep
		}

		copiado = false;  // reset variable
		pthread_mutex_unlock(&mutex);  // unlock
	}

	for (j = 0; j < NUM_THREADS; j++) {
		pthread_join(thid[j], NULL);
	}

	exit(0);
}
	

	

