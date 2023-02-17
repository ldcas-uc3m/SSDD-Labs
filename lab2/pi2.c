#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 1E7
#define d 1E-7
#define NUM_THREADS 50


double PI = 0.0;

// sync id
pthread_mutex_t mutex_id;
pthread_cond_t c_id;
bool copiado = false;

// sync pi
pthread_mutex_t mutex_pi;


void calcula(int* id) {
    double sum=0.0, x;

    // get id
	pthread_mutex_lock(&mutex_id);

	int mid = *id;

	copiado = true;
	pthread_cond_signal(&c_id);
	pthread_mutex_unlock(&mutex_id);

    for (int i = mid; i < N; i += NUM_THREADS) {
        x = d * i;
        sum += sqrt(4 * (1 - x*x));
    }

    pthread_mutex_lock(&mutex_pi);
    PI = PI + d * 2 * sum;
    pthread_mutex_unlock(&mutex_pi);

    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
    // init threads, mutex and cond
	pthread_attr_t attr;
	pthread_t thid[NUM_THREADS];

	pthread_cond_init(&c_id, NULL);
	pthread_mutex_init(&mutex_id, NULL);

	pthread_mutex_init(&mutex_pi, NULL);

	pthread_attr_init(&attr);
    
    // time
    struct timeval t1, t2;
    long t;
    gettimeofday(&t1, 0);

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&thid[i], NULL, (void*) calcula, &i) == -1) {
			printf("Error al crear los threads\n");
			exit(0);
		}

		// mutex logic
		pthread_mutex_lock(&mutex_id);

        // wait for thread to copy id
		while (!copiado) {
			pthread_cond_wait(&c_id, &mutex_id);
		}

		copiado = false;
		pthread_mutex_unlock(&mutex_id);
    }

    // wait for threads to end
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(thid[i], NULL);
	}

    gettimeofday(&t2, 0);
    t = (t2.tv_sec - t1.tv_sec)*1000000 + t2.tv_usec - t1.tv_usec;
    printf("El tiempo es %f ms\n", (t / 1000.0));

    printf("PI = %.9f\n", PI);

    // cleanup
	pthread_cond_destroy(&c_id);
	pthread_mutex_destroy(&mutex_id);
	pthread_mutex_destroy(&mutex_pi);

    exit(0);
}