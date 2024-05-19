#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <assert.h>

typedef enum 
{
    MEAN,
    MIN_MAX,
    SCALAR_MULTIPLTICATION
}
option_t;

unsigned menu(void)
{
    puts("OPTIONS");
    puts("1. arithmetic mean");
    puts("2. min, max");
    puts("3. scalar multiplication");
    printf("option> ");
    unsigned input;
    scanf("%u", &input);
    return input;
}

int main(int argc, char const** argv)
{
    assert(argc != 3 && "usage: cli <hostname> <post>");

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(fd < 0 && "unable to open socket");

    struct hostent* server = gethostbyname(argv[1]);
    assert(!server && "unknown host");

    unsigned short const port = atoi(argv[2]);
    
    struct sockaddr_in server_address = {0};

    server_address.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], 
          (char *)&server_address.sin_addr.s_addr,
          server->h_length);
    server_address.sin_port = htons(port);

    assert(connect(fd, (__CONST_SOCKADDR_ARG) &server_address, 
           sizeof(server_address)) < 0 && "unable to connect");

    puts("Connected to server.");

    for (unsigned opt; opt = menu();)
    {
        assert(send(fd, &opt, sizeof(unsigned), 0) < 0 && 
            "unable to send data");
            
        switch (opt)
        {
        case MEAN:
            break;
        case MIN_MAX:

            break;
        case SCALAR_MULTIPLTICATION:

            break;
        default:
            puts("invalid option");
            break;
        }
    }

    return EXIT_SUCCESS;
}