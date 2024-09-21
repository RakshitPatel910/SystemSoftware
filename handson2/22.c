/*
========================================================================================================
Name : 22
Author : Rakshit Patel
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 18 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

int main() {
    	int fifo_fd = open("myfifo", O_RDONLY | O_NONBLOCK);

    	struct timeval timeout;
    	timeout.tv_sec = 10;
    	timeout.tv_usec = 0;
    
    	fd_set read_fds;
    	FD_ZERO(&read_fds);
    	FD_SET(fifo_fd, &read_fds);
    
    	int result = select(fifo_fd + 1, &read_fds, NULL, NULL, &timeout);

    	if (result == 0) {
        	printf("Timeout: No data received within 10 seconds.\n");
    	}
       	else {
        	char buffer[256];
        	ssize_t bytes_read = read(fifo_fd, buffer, sizeof(buffer) - 1);
        	if (bytes_read > 0) {
            		buffer[bytes_read] = '\0'; 
            		printf("Received data: %s\n", buffer);
        	}
    	}

    	close(fifo_fd);
    	
	return 0;
}

/*
========================================================================================================

./a.out 
Timeout: No data received within 10 seconds.


./a.out
Received data: Message to FIFO!

echo "Message to FIFO!" > myfifo

========================================================================================================
*/


