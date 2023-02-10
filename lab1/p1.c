#include <stdio.h>

int main(int argc, char* argv[]) {
	// ten en cuenta que **argv es equivalente a *argv[] 
	printf("Programa P1 \n");

	for (unsigned int i = 1; i < argc; i++) {
		// argv[0] es el ejecutable
		printf("Argumento %i: %s\n", i, argv[i]);
	}

	return 0;
}