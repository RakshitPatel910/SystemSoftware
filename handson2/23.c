/*
========================================================================================================
Name : 23
Author : Rakshit Patel
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 19 Sept, 2024.
========================================================================================================
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>

int main(){	
	int pfd[2];
	pipe(pfd);

    	//mkfifo("23_myfifo", S_IRWXU);

    	long maxFiles = sysconf(_SC_OPEN_MAX);

    	printf("Maximum number of files that can be opened is: %ld\n", maxFiles);
    	printf("Maximum size of pipe: %d\n", PIPE_BUF);
	
	return 0;
}

/*
========================================================================================================

./a.out
Maximum number of files that can be opened is: 1024
Maximum size of pipe: 4096

========================================================================================================
*/

