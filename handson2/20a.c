/*
========================================================================================================
Name : 20a
Author : Rakshit Patel
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 18 Sept, 2024.
========================================================================================================
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
    	char *msg = NULL;
    	size_t size = 0;
    	const char *fifoPath = "./20-fifo";

    	mkfifo(fifoPath, 0666 );

    	while (1) {
        	int fd = open(fifoPath, O_WRONLY);

        	printf("Enter message (empty to exit):\n");
        	getline(&msg, &size, stdin);

        	if (msg[0] == '\n') { 
            		write(fd, "exit", 4); 
            		close(fd);
          		break;
        	}

        	write(fd, msg, size);
        	close(fd);
    	}

//    	free(msg);
    	return 0;
}

/*
========================================================================================================

./a.out
Enter message (empty to exit):
hi
Enter message (empty to exit):
2nd msg
Enter message (empty to exit):


./b.out 
hi


2nd msg



========================================================================================================
*/

