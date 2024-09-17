/*
========================================================================================================
Name : 16
Author : Rakshit Patel
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
Date: 17 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	int pipefd[2];
	pid_t child_pid;
	char parent_to_child_msg[] = "Message from parent";
	char child_to_parent_msg[] = "Message from child";
   	char buffer[100];

    	pipe(pipefd);

    	child_pid = fork();

    	if (child_pid == 0) {
        	ssize_t n = read(pipefd[0], buffer, sizeof(buffer) - 1);
        	buffer[n] = '\0';
        	printf("Child received: %s\n", buffer);
	
		printf("Chile sent: %s\n", child_to_parent_msg);
        	write(pipefd[1], child_to_parent_msg, strlen(child_to_parent_msg));

		close(pipefd[1]);
        	close(pipefd[0]);
    	} 
    	else {
        	write(pipefd[1], parent_to_child_msg, strlen(parent_to_child_msg));
        	printf("Parent sent: %s\n", parent_to_child_msg);

        	sleep(2);

        	ssize_t m = read(pipefd[0], buffer, sizeof(buffer) - 1);
        	buffer[m] = '\0';
        	printf("Parent received: %s\n", buffer);
                
		close(pipefd[0]);
        	close(pipefd[1]); 
    	}

    	return 0;
}

/*
========================================================================================================
Output:

./a.out 
Parent sent: Message from parent
Child received: Message from parent
Chile sent: Message from child
Parent received: Message from child

========================================================================================================
*/
