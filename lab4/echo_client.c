/*
Echo client with RPCs
*/

#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

#include "echo.h"


#define MAX_LINE 256


ssize_t readLine(int fd, void *buffer, size_t n)
{
	ssize_t numRead;  /* num of bytes fetched by last read() */
	size_t totRead;	  /* total bytes read so far */
	char *buf;
	char ch;


	if (n <= 0 || buffer == NULL) { 
		errno = EINVAL;
		return -1; 
	}

	buf = buffer;
	totRead = 0;
	
	for (;;) {
        	numRead = read(fd, &ch, 1);	/* read a byte */

        	if (numRead == -1) {	
            		if (errno == EINTR)	/* interrupted -> restart read() */
                		continue;
            	else
			return -1;		/* some other error */
        	} else if (numRead == 0) {	/* EOF */
            		if (totRead == 0)	/* no byres read; return 0 */
                		return 0;
			else
                		break;
        	} else {			/* numRead must be 1 if we get here*/
            		if (ch == '\n')
                		break;
            		if (ch == '\0')
                		break;
            		if (totRead < n - 1) {		/* discard > (n-1) bytes */
				totRead++;
				*buf++ = ch; 
			}
		} 
	}
	
	*buf = '\0';
    	return totRead;
}



void echoprog_1(char *host) {
	CLIENT *clnt;
	enum clnt_stat retval_1;
	char *result_1;
	char echo_1_s[MAX_LINE];

	/*
	Main program
	*/

	// start client

	clnt = clnt_create(host, ECHOPROG, ECHOPROGVER, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}


	// main loop
    while (true) {
        readLine(STDIN_FILENO, echo_1_s, MAX_LINE);
		
		result_1 = (char*) malloc(256);  // reserve mem for result
        
		// send message
		retval_1 = echo_1(echo_1_s, &result_1, clnt);  // return value
		
        if (strcmp(result_1, "EXIT") == 0) break;

		if (retval_1 != RPC_SUCCESS) {
			clnt_perror (clnt, "Call failed");
		} 
		else {
			printf("Server: %s\n", result_1);
		}
		
		free(result_1);

    }
	
	clnt_destroy (clnt);

	// strcpy(echo_1_s, "Prueba");  // copy argument



}


int main (int argc, char *argv[]) {
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];

	echoprog_1(host);
	
	exit (0);
}

