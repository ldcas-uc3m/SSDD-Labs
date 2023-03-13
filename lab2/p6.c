#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_LECTORES	10
#define NUM_THREADS	11    // 10 lectores y 1 escritor
#define ITER 		40


int	num_lectores;
int	recurso = 0;
unsigned long int thd_id;


// sync
pthread_mutex_t	mutex_recurso;
pthread_mutex_t	mutex_lectores;
pthread_cond_t cond_first;


// FIXME: escritor ejecuta sin haber esperado a que todos lean

void lector(void) {
	int j;
	int s;
	double k;

	for (j = 0; j < ITER; j++) {
		k = (double) rand_r((unsigned int*) &s) / RAND_MAX;	
		usleep((int) 1 + (k * 6000000)); // duerme entre 1 y 9 s

		// add one to reader count
		if (pthread_mutex_lock(&mutex_lectores) != 0) {
			printf(".......  Error en mutex lock 1 \n");
		}

		num_lectores++;

		// read resource
		if (num_lectores == 1) {  // first reader
			thd_id = (unsigned long int) pthread_self();
			printf("Primer %lu \n", thd_id);
			pthread_mutex_lock(&mutex_recurso);
		}

		if (pthread_mutex_unlock(&mutex_lectores) != 0) {
			printf(".......  Error en mutex unlock 1 \n");
		}


		printf("       Ejecuta el lector %lu lee  %d \n", (unsigned long int) pthread_self(), recurso);


		// remove one from reader count
		if (pthread_mutex_lock(&mutex_lectores) != 0) {
			printf(".......  Error en mutex lock 2 \n");
		}

		num_lectores--;

		// unlock the resource once everyone's finished
		if (thd_id == pthread_self()) {  // only the one who locked can unlock
			
			while (num_lectores > 0) {  // wait for the rest to finish
				pthread_cond_wait(&cond_first, &mutex_lectores);
			}
			printf("Ultimo %lu \n", (unsigned long int) pthread_self());
			if (pthread_mutex_unlock(&mutex_recurso) != 0) {
				printf("________________ Error en unlock\n");
			}
		} else {  // wakeup first to see if they are the last one
			pthread_cond_signal(&cond_first);
		}

		if (pthread_mutex_unlock(&mutex_lectores) != 0) {
			printf(".......  Error en mutex unlock 2 \n");
		}
	}
	
	pthread_exit(NULL);
}


void escritor(void) {
	int j;
	int s;
	double k;

	for (j = 0; j < ITER; j++) {
		k = (double) rand_r((unsigned int*) &s) / RAND_MAX;	
		usleep((int) 2 + (k * 5000000));  // duerme entre 2 y 7 s

		pthread_mutex_lock(&mutex_recurso);

		recurso++;

		// write
		printf("                                                          Escritor: Nuevo valor %d\n", recurso);

		pthread_mutex_unlock(&mutex_recurso);
	}
	
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	int j;
	pthread_attr_t attr;
	pthread_t thid[NUM_THREADS];
	pthread_mutexattr_t mattr;
	pthread_cond_init(&cond_first, NULL);

	struct timeval t;
	gettimeofday(&t, NULL);
	srand(t.tv_sec);	// se inicializa la semilla de no. pseudoaleatorios

	pthread_attr_init(&attr);

	pthread_mutexattr_init(&mattr);
	pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_ERRORCHECK);


	pthread_mutex_init(&mutex_recurso, &mattr);
	pthread_mutex_init(&mutex_lectores, &mattr);

	// create readers
	for (j = 0; j < NUM_LECTORES; j++) {
		if (pthread_create(&thid[j], NULL, (void*) lector, NULL) == -1) {
			printf("Error al crear los threads lectores\n");
			exit(0);
		}
	}

	// create writer
	if (pthread_create(&thid[j], NULL, (void*) escritor, NULL) == -1) {
		printf("Error al crear el escritor\n");
		exit(0);
	}

	for (j = 0; j < NUM_THREADS; j++) {
		pthread_join(thid[j], NULL);
	}


	// cleanup
	pthread_cond_destroy(&cond_first);
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mutex_recurso);
	pthread_mutex_destroy(&mutex_lectores);

	exit(0);

}
	

	

