#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/linked_list.h"



int main(int argc, char* argv[]) {
	printf("--Programa P5--\n");

	// init linked list
	List list;
	init(&list);

	for (unsigned int i = 1; i < argc; i++) {

		// convert to int
		char* end;
		long int converted_arg = strtol(argv[i], &end, 10);
		
		if (*end != '\0') {
			printf("Argumento %i: Error de conversion\n", i);
			perror("Error de conversión\n");

			return -1;
		} else {
			printf("Argumento %i: %i\n", i, (int) converted_arg);
		}
		
		// copy string
		char* arg;
		arg = (char*) malloc(strlen(argv[1] + 1));
		strcpy(arg, argv[i]);

		// save element
		int err = set(&list, arg, converted_arg);
		if (err < 0)
			return -1;
	}

	// print list
	printf("Lista: ");
	printList(list);

	// cleanup
	destroy(&list);

	return 0;
}