/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdint.h>

#include "calc.h"

#define EXIT 4

// global variables
static CLIENT *clnt;

void
calc_prog_1(char *host)
{
	CLIENT *clnt;
	output_mean  *result_1;
	input_vector  mean_1_arg;
	output_min_max  *result_2;
	input_vector  min_max_1_arg;
	output_scalar_multiplication  *result_3;
	input_scalar_multiplication  scalar_multiplication_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, CALC_PROG, CALC_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = mean_1(&mean_1_arg, clnt);
	if (result_1 == (output_mean *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = min_max_1(&min_max_1_arg, clnt);
	if (result_2 == (output_min_max *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = scalar_multiplication_1(&scalar_multiplication_1_arg, clnt);
	if (result_3 == (output_scalar_multiplication *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

void* option(void* arg)
{
	int const fd = (intptr_t) arg;

	for (unsigned opt;;)
	{

		if (recv(fd, &opt, sizeof(unsigned), 0) < 0)
		{
			puts("unable to recover data");
			return NULL;
		}

		switch (opt)
		{
		case MEAN:
			{
				output_mean  *result_1;
				input_vector  mean_1_arg;

				if (recv(fd, &mean_1_arg.y.y_len, sizeof(unsigned), 0) < 0)
				{
					puts("unable to send data");
					return NULL;
				}

				if (!(mean_1_arg.y.y_val = malloc(sizeof(int) * 
												  mean_1_arg.y.y_len)))
				{
					puts("unable to allocate memory");
					return NULL;
				}

				if (recv(fd, mean_1_arg.y.y_val, 
						sizeof(int) * mean_1_arg.y.y_len, 0) < 0)
				{
					puts("unable to send data");
					return NULL;
				}

				result_1 = mean_1(&mean_1_arg, clnt);
				if (result_1 == (output_mean*) NULL) {
					clnt_perror (clnt, "call failed");
				}

				free(mean_1_arg.y.y_val);

				if (send(fd, result_1, sizeof(output_mean), 0) < 0)
				{
					puts("unable to send data");
					return NULL;
				}
			}
			break;
		case MIN_MAX:

			break;

		case SCALAR_MULTIPLICATION:

			break;
		case EXIT:
			close(fd);
		default:
			return NULL;
		}
	}
}

int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 3) {
		printf ("usage: %s <server_host> <port>\n", argv[0]);
		exit (1);
	}
	host = argv[1];

#ifndef	DEBUG
	clnt = clnt_create (host, CALC_PROG, CALC_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	unsigned short port = atoi(argv[2]);

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	assert(fd >= 0 && "unable to open socket");

	struct sockaddr_in server_address = {0};

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = INADDR_ANY;

	assert(bind(fd, (__CONST_SOCKADDR_ARG) &server_address, 
		        sizeof(server_address)) >= 0 && "unable to bind");

	assert(listen(fd, 5) >= 0 && "unable to listen to connections");

	for (unsigned long c = 0, thread[50] = {0};;)
	{
		struct sockaddr_in client_address;
		socklen_t client_size = sizeof(client_address);
		int clfd = accept(fd, (__SOCKADDR_ARG) &client_address, 
						  &client_size);
		if (clfd < 0)
		{
			puts("unable to accept connection");
			continue;
		}

		pthread_create(thread + c++, NULL, option, (void*) (intptr_t) clfd);
	}

	// calc_prog_1 (host);
exit (0);
}
