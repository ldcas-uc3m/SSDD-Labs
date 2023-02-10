#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"


void obtenerMinMax(int size, int *array, int *min, int *max) {
	// obtiene el mínimo y el máximo de un array, guardándolo en
	// min y max, variables definidas en el main()

	// no se puede retornar una variable local, ya que se puede borrar
	// al terminar la función

	int num_min, num_max = array[0];

	for(unsigned int i = 0; i < size; i++) {

		if (array[i] < num_min) num_min = array[i];
		if (array[i] > num_max) num_max = array[i];
	}

	*min = num_min;
	*max = num_max;

	return;
}


int main(int argo, char *argv[]) {
	// ten en cuenta que **argv es equivalente a *argv[] 
	printf("Programa P4\n");

	// create (dynamically) an array to save the arguments
	int *v;
	v = (int*)malloc((argo - 1) * sizeof(int));

	// create (dynamically) an array to save the string arguments
	char **s;
	s = (char**)malloc((argo - 1) * sizeof(char*));  // array to store pointers to strings

	for (unsigned int i = 1; i < argo; i++) {
		// copy the string
		s[i-1] = (char*)malloc(strlen(argv[1] + 1));  // +1 to take into account \0
		strcpy(s[i-1], argv[i]);

		char *end;  // for error detection
		long int converted_arg = strtol(s[i-1], &end, 10);
		// error detection for strtol
		if (*end != '\0') {
			printf("Argumento %i: Error de conversion\n", i);
		} else {
			v[(i-1)] = converted_arg;  // argv[0] es el nombre del ejecutable
			printf("Argumento %i: %li\n", i, converted_arg);
		}
	}
	// print min/max
	int min, max;

	obtenerMinMax(argo - 1, v, &min, &max);

	printf("El mínimo es: %i\n", min);
	printf("El máximo es: %i\n", max);

	// cleanup
	for (unsigned int i; i < (argo - 1); i++) {
		free(s[i]);
	}

	free(v);

	return 0;
}