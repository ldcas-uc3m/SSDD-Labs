#include <stdio.h>
#include <stdlib.h>


void obtenerMinMax(int size, int *array, int *min, int *max) {
	// obtiene el mínimo y el máximo de un array, guardándolo en
	// min y max, variables definidas en el main()

	// no se puede retornar una variable local, ya que se puede borrar
	// al terminar la función

	int num_min, num_max = array[0];

	for (unsigned int i = 0; i < size; i++) {

		if (array[i] < num_min) num_min = array[i];
		if (array[i] > num_max) num_max = array[i];
	}

	*min = num_min;
	*max = num_max;

	return;
}


int main(int argo, char *argv[]) {
	// ten en cuenta que **argv es equivalente a *argv[] 
	printf("Programa P3\n");

	// create (dynamically) an array to save the arguments
	int *v;
	v = (int*) malloc((argo - 1) * sizeof(int));

	for (unsigned int i = 1; i < argo; i++) {
		char *end;  // for error detection

		long int converted_arg = strtol(argv[i], &end, 10);
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


	free(v);  // REMEMBER THIS

	return 0;
}