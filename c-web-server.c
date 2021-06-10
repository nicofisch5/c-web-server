#include <errno.h>
#include <stdio.h>
#include <string.h>
//#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
//#include <netdb.h>	//hostent
#include <arpa/inet.h>

extern int errno;

const int PORT = 55555;
const int NB_REQUESTS = 1;

struct HttpRequest {
   char method[8];
   char *path;
   char *agent;
};

/*
GET /fichier.html HTTP/1.1
Host: localhost:55555
Connection: keep-alive
sec-ch-ua: " Not;A Brand";v="99", "Google Chrome";v="91", "Chromium";v="91"
sec-ch-ua-mobile: ?0
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.77 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,;q=0.8,application/signed-exchange;v=b3;q=0.9
Sec-Fetch-Site: none
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate, br
Accept-Language: en-GB,en;q=0.9,fr-FR;q=0.8,fr;q=0.7,en-US;q=0.6
*/

void send_message_to_client(int incoming_socket);
int parse_http_request(char *buffer, struct HttpRequest *request);


int main(int argc, char **argv)
{
    int errnum;
    int port = PORT;
    int socket_descriptor;
    int incoming_socket;
    int addr_len;
    char buffer[1024] = {0};
    struct sockaddr_in server, client;
    struct HttpRequest *incomingRequest;

    printf("Welcome to c-web-server!\n");

    // Check number of arguments, if not enough display error and finish the program
	/*if (argc < 2) {
		printf("Missing argument\n");
  		exit(-1);
	}*/

    if (argc >= 2) {
        port = (int)*argv[1];
    }

    // v3 Load a config file

    // v1 Create socket on port
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
    server.sin_port = htons(port);

    // Bind socket to a particular "address and port" combination.
    // It needs a sockaddr_in struct
    if(bind(socket_descriptor, (struct sockaddr *)&server , sizeof(server)) < 0)
    {
	    printf("Bind failed\n");

        errnum = errno;
        fprintf(stderr, "Error: %d - %s\n", errno, strerror(errnum));
  		exit(-1);
    }
    printf("Bind OK\n");

    // v1 Put the socket in listening mode
    listen(socket_descriptor, NB_REQUESTS);
    printf("Put the socket in listening mode and accept incoming request\n");
    
    // v1 Wait for http request
    addr_len = sizeof(struct sockaddr_in);
    while ((incoming_socket = accept(socket_descriptor, (struct sockaddr *)&client, (socklen_t*)&addr_len)) > 0)
    {
        printf("It seems we received something...\n");
        printf("sin_family: %d\n", client.sin_family);
        printf("sin_port: %d\n", client.sin_port);
        printf("sin_addr: %d\n", client.sin_addr.s_addr);
        printf("sin_addr: %s\n", inet_ntoa(client.sin_addr));
        //printf("sin_zero: %hhn\n", client.sin_zero);

        // v1 Read message from client
        if (recv (incoming_socket, buffer, 1024, 0))
        {
            printf("Message from client: %s\n", buffer);
            // Analyze the request
            if (parse_http_request(buffer, incomingRequest) < 0) {
                ;
            }
        }

        // v0 Write a ack to the client
        send_message_to_client(incoming_socket);
    }
    
    /**
     * When a request occurs then
     * v1 try to find the requested file on the fs
     * v2 create a new process
     * v3 create a new thread
    */

   // v1 Send or write the file to the socker
   //ssize_t send(int sockfd, const void *buf, size_t len, int flags);

    // v3 Log
}

void send_message_to_client(int incoming_socket)
{
    int ssize_t;
    char *msg = "HTTP/1.1 200 OK\nServer: c-web-server/0.1\nContent-Type: text/html\nConnection: close\n\nThis is my first HTTP response";

    ssize_t = send(incoming_socket, msg, strlen(msg), 0);
    printf("Message send to client: %s", msg);
}

int parse_http_request(char *buffer, struct HttpRequest *request)
{
    return -1;
}