#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <assert.h>

#include "calc.h"

#define EXIT 4

unsigned menu(void)
{
    puts("OPTIONS");
    puts("1. arithmetic mean");
    puts("2. min, max");
    puts("3. scalar multiplication");
    puts("4. exit");
    printf("option> ");
    unsigned input;
    scanf("%u", &input);
    return input;
}

int* scan_vector(unsigned long size)
{
    int* vector = malloc(sizeof(int) * size);
    if (!vector)
        return NULL;
    for(unsigned long i = 0; i < size; ++i)
        scanf("%d", vector + i);
    return vector;
}

void mean(int fd)
{
    unsigned long size;
    printf("Enter vector size: ");
    scanf("%lu", &size);
    puts("Enter vector values:");
    int* vector;
    assert((vector = scan_vector(size)) && "unable to allocate enough memory");

    assert(send(fd, (unsigned*) &size, sizeof(unsigned), 0) >= 0 && 
        "unable to send data");
    assert(send(fd, vector, sizeof(int) * size, 0) >= 0 && 
        "unable to send data");

    free(vector);

    output_mean o;
    assert(recv(fd, &o, sizeof(output_mean), 0) >= 0 && 
        "unable to recover data");
    
    if (o.err != NO_ERROR)
    {
        printf("unable to find arithmetic mean value\nerr code %u\n", o.err);
        return;
    }

    printf("arithmetic mean value: %lf\n", o.mean);
}

void min_max(int fd)
{
    unsigned long size;
    printf("Enter vector size: ");
    scanf("%lu", &size);
    puts("Enter vector values:");
    int* vector;
    assert((vector = scan_vector(size)) && "unable to allocate enough memory");

    assert(send(fd, (unsigned*) &size, sizeof(unsigned), 0) >= 0 && 
        "unable to send data");
    assert(send(fd, vector, sizeof(int) * size, 0) >= 0 && 
        "unable to send data");

    free(vector);

    output_min_max o;
    assert(recv(fd, &o, sizeof(output_min_max), 0) >= 0 && 
        "unable to recover data");
    
    if (o.err != NO_ERROR)
    {
        printf("unable to find min and max values\nerr code %u\n", o.err);
        return;
    }

    printf("min value: %d, max value: %d\n", o.pair.first, o.pair.second);
}

void scalar_multiplication(int fd)
{
    unsigned long size;
    printf("Enter vector size: ");
    scanf("%lu", &size);
    puts("Enter vector values:");
    int* vector;
    assert((vector = scan_vector(size)) && "unable to allocate enough memory");

    assert(send(fd, (unsigned*) &size, sizeof(unsigned), 0) >= 0 && 
        "unable to send data");
    assert(send(fd, vector, sizeof(int) * size, 0) >= 0 && 
        "unable to send data");

    free(vector);

    double d;
    printf("Enter double: ");
    scanf("%lf", &d);
    assert(send(fd, &d, sizeof(double), 0) >= 0 && "unable to send data");

    output_scalar_multiplication o;
    assert(recv(fd, &o, sizeof(output_scalar_multiplication), 0) >= 0 && 
        "unable to recover data");

    if (o.err != NO_ERROR)
    {
        printf("unable to find scalar multiplication\nerr code %u\n", o.err);
        return;
    }

    o.y.y_val = NULL;

    assert((o.y.y_val = malloc(sizeof(double) * o.y.y_len)) && 
        "unable to allocate memory");

    assert(recv(fd, o.y.y_val, sizeof(double) * o.y.y_len, 0) >= 0 &&
        "unable to recover data");
    
    puts("new vector:");
    for (unsigned long i = 0; i < o.y.y_len; ++i)
    {
        printf("%lf ", o.y.y_val[i]);
    }
    puts("");

    free(o.y.y_val);
}

int main(int argc, char const** argv)
{
    assert(argc == 3 && "usage: cli <hostname> <post>");

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(fd >= 0 && "unable to open socket");

    struct hostent* server = gethostbyname(argv[1]);
    assert(server && "unknown host");

    unsigned short const port = atoi(argv[2]);
    
    struct sockaddr_in server_address = {0};

    server_address.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], 
          (char *)&server_address.sin_addr.s_addr,
          server->h_length);
    server_address.sin_port = htons(port);

    assert(connect(fd, (__CONST_SOCKADDR_ARG) &server_address, 
                   sizeof(server_address)) >= 0 && "unable to connect");

    puts("Connected to server.");

    for (unsigned opt = menu();; opt = menu())
    {
        assert(send(fd, &opt, sizeof(unsigned), 0) >= 0 && 
            "unable to send data");

        switch (opt)
        {
        case MEAN:
            mean(fd);
            break;
        case MIN_MAX:
            min_max(fd);
            break;
        case SCALAR_MULTIPLICATION:
            scalar_multiplication(fd);
            break;
        case EXIT:
            return EXIT_SUCCESS;
        default:
            puts("invalid option");
            break;
        }
    }

    return EXIT_SUCCESS;
}