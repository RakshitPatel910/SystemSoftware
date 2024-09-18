/*
========================================================================================================
Name : 15
Author : Rakshit Patel
Description : Write a simple program to send some data from parent to the child process.
Date: 17 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    	int fd[2];
    	pid_t child_pid;
    	char input[] = "Data through pipe";
    	char buffer[50];

    	pipe(fd);

    	child_pid = fork();

    	if (child_pid == 0) {
        	close(fd[1]);
        	ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        	buffer[n] = '\0';
        	printf("Received in child: %s\n", buffer);
        	close(fd[0]);
    	} else {
        	close(fd[0]);
        	printf("Sending from parent: %s\n", input);
        	ssize_t m = write(fd[1], input, strlen(input));
        	close(fd[1]);
    	}

    	return 0;
}

/*
========================================================================================================

./a.out
Sending from parent: Data through pipe
Received in child: Data through pipe

========================================================================================================
*/

