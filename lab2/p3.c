#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>


#define NUM_THREADS	10
#define ITER 		10


// sync ids
pthread_mutex_t mutex_id;
pthread_cond_t c_id;  // variable condicional de bloqueo
bool copiado = false;  // variable condicional de control

// sync 
pthread_mutex_t mutex_turn;
pthread_cond_t c_turn;
unsigned int turn = 0;  // turno de hilo i


void funcion(int* id) {
	int s;
	double k;
	int mid = *id;  // cada thread recibe un número (0 o 1)

	// mutex logic
	pthread_mutex_lock(&mutex_id);
	copiado = true;  // update conditional variable
	pthread_cond_signal(&c_id);  // signal all sleeping threads
	pthread_mutex_unlock(&mutex_id);

	for (int j = 0; j < ITER; j++) {

		// wait for my turn
		pthread_mutex_lock(&mutex_turn);
		while (turn != mid) {
			pthread_cond_wait(&c_turn, &mutex_turn);
		}
		pthread_mutex_unlock(&mutex_turn);

		k = (double) rand_r((unsigned int*) &s) / RAND_MAX;	
		usleep((int) (k * 100000)); // duerme entre 0 y 100 ms
		printf("Ejecuta el thread %d iteracion %d \n", mid, j);

		// give turn to next one
		pthread_mutex_lock(&mutex_turn);

		turn = (turn + 1) % NUM_THREADS;

		pthread_cond_broadcast(&c_turn);  // signal all sleeping threads
		pthread_mutex_unlock(&mutex_turn);
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
	pthread_cond_init(&c_id, NULL);
	pthread_mutex_init(&mutex_id, NULL);

	pthread_cond_init(&c_turn, NULL);
	pthread_mutex_init(&mutex_turn, NULL);

	pthread_attr_init(&attr);

	for (int j = 0; j < NUM_THREADS; j++) {
		if (pthread_create(&thid[j], NULL, (void*) funcion, &j) == -1) {
			printf("Error al crear los threads\n");
			exit(0);
		}

		// mutex logic
		pthread_mutex_lock(&mutex_id);  // lock

		while (!copiado) {  // wait for thread to copy id
			pthread_cond_wait(&c_id, &mutex_id);  // sleep
		}

		copiado = false;  // reset variable
		pthread_mutex_unlock(&mutex_id);  // unlock
	}

	for (int j = 0; j < NUM_THREADS; j++) {
		pthread_join(thid[j], NULL);
	}

	// cleanup
	pthread_cond_destroy(&c_id);
	pthread_mutex_destroy(&mutex_id);
	
	pthread_cond_destroy(&c_turn);
	pthread_mutex_destroy(&mutex_turn);

	exit(0);
}
	

	

