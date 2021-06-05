#include <stdio.h>
//#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/stat.h>

int main(int argc, char **argv)
{
    printf('Welcome to c-web-server!');

    // Check number of arguments, if not enough display error and finish the program
	if (argc < 3) {
		printf("Missing argument\n");
  		exit(-1);
	}

    // v3 Load a config file
    // v1 Create socket on port XXX
    // v1 Listen on this socket port
    // v1 Wait for http request
    /**
     * When a request occurs then
     * v1 try to find the requested file on the fs
     * v2 create a new process
     * v3 create a new thread
    */

}
