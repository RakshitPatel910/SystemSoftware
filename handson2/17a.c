/*
========================================================================================================
Name : 17.a
Author : Rakshit Patel
Description : Write a program to execute ls -l | wc.
		a. Use dup
Date: 17 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int fd[2];
    	int child_pid;
    	pipe(fd);

    	child_pid = fork();

    	if (child_pid == 0) {
		close(0);
		dup(fd[0]);
		close(fd[1]);

		execl("/usr/bin/wc", "wc", NULL);		
		perror("execl");
		exit(1);
	}
       	else {
        	close(1);
		dup(fd[1]);
		close(fd[0]);

		execl("/usr/bin/ls", "ls", "-l", NULL);
		perror("execl");
		exit(1);
    	}

    	return 0;
}

/*
========================================================================================================
Output:
./a.out
     31     272    1963

========================================================================================================
*/
