#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>


#define NUM_THREADS	 5
#define ITER 		10


// sync
pthread_mutex_t mutex;
pthread_cond_t c;  // variable condicional de bloqueo
bool copiado = false;  // variable condicional de control


void funcion(int* id) {
	int s;
	double k;

	// mutex logic
	pthread_mutex_lock(&mutex);
	int mid = *id;  // cada thread recibe un número (0 o 1)
	copiado = true;  // update conditional variable
	pthread_cond_signal(&c);  // signal one sleeping thread
	pthread_mutex_unlock(&mutex);

	for (int j = 0 ; j < ITER; j++) {
		k = (double) rand_r((unsigned int*) &s) / RAND_MAX;	
		usleep((int) (k * 100000)); // duerme entre 0 y 100 ms
		printf("Ejecuta el thread %d iteracion %d \n", mid, j);
	}
	
	pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
	pthread_attr_t attr;
	pthread_t thid[NUM_THREADS];

	// semilla de no. pseudoaleatorios
	struct timeval t;
	gettimeofday(&t, NULL);
	srand(t.tv_sec);	

	// init mutex and cond
	pthread_cond_init(&c, NULL);
	pthread_mutex_init(&mutex, NULL);

	pthread_attr_init(&attr);

	for (int j = 0; j < NUM_THREADS; j++) {
		if (pthread_create(&thid[j], NULL, (void*) funcion, &j) == -1) {
			printf("Error al crear los threads\n");
			exit(0);
		}

		// mutex logic
		pthread_mutex_lock(&mutex);  // lock

		while (!copiado) {  // wait for thread to copy id
			// implicit unlock
			pthread_cond_wait(&c, &mutex);  // sleep
			// implicit lock
		}

		copiado = false;  // reset variable
		pthread_mutex_unlock(&mutex);  // unlock
	}

	// wait for threads to end
	for (int j = 0; j < NUM_THREADS; j++) {
		pthread_join(thid[j], NULL);
	}

	// cleanup
	pthread_cond_destroy(&c);
	pthread_mutex_destroy(&mutex);
	
	exit(0);
}
	

	

