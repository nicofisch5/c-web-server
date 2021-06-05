#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
//#include <netdb.h>	//hostent
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    const int PORT = 55555;
    int socket_descriptor;
    struct sockaddr_in server;

    printf("Welcome to c-web-server!");

    // Check number of arguments, if not enough display error and finish the program
	/*if (argc < 3) {
		printf("Missing argument\n");
  		exit(-1);
	}*/

    // v3 Load a config file

    // v1 Create socket on port XXX
	socket_descriptor = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_descriptor == -1)
	{
		printf("Could not create socket\n");
        exit(-1);
	}
	printf("Socket #%d has been created\n", socket_descriptor);
    
    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind socket to a particular "address and port" combination.
    // It needs a sockaddr_in struct
    if(bind(socket_descriptor, (struct sockaddr *)&server , sizeof(server)) < 0)
    {
	    printf("Bind failed\n");
  		exit(-1);
    }
    printf("Bind OK\n");

    // v1 Listen on this socket port
    
    // v1 Wait for http request
    
    /**
     * When a request occurs then
     * v1 try to find the requested file on the fs
     * v2 create a new process
     * v3 create a new thread
    */

   // v1 Send or write the file to the socker
   //ssize_t send(int sockfd, const void *buf, size_t len, int flags);

}
