#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	// ten en cuenta que **argv es equivalente a *argv[] 
	printf("--Programa P2--\n");

	for (unsigned int i = 1; i < argc; i++) {
		char* end;  // for error detection

		long int converted_arg = strtol(argv[i], &end, 10);
		// error detection for strtol
		if (*end != '\0') {
			printf("Argumento %i: Error de conversion\n", i);
		} else {
			printf("Argumento %i: %li\n", i, converted_arg);
		}
	}

	return 0;
}