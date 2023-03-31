/*
Echo server with RPCs
*/

#include "echo.h"


bool_t echo_1_svc(char *s, char **result,  struct svc_req *rqstp) {
	/*
	Echo function (server)
	*/
	bool_t retval;

	*result = (char*) malloc(256);  // allocate space for result

	if (strcmp(s, "EXIT") == 0) {
		printf("Client disconnected\n");
	}
	else {
		printf("Client: %s\n", s);
	}

	sprintf(*result, "%s", s);  // return input (echo)

	return retval;
}


int echoprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result) {
	/*
	Free function
	*/

	xdr_free (xdr_result, result);  // does it all on its own

	return 1;
}
