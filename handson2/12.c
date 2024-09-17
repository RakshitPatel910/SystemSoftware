/*
========================================================================================================
Name : 12
Author : Rakshit Patel
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
Date: 17 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main() {
	int pid = fork();

	if( pid == -1 ){
		printf("error\n");
		return 0;
	}

	if( pid == 0 ){
		printf( "child process : %d\n", getpid() );
		printf( "parent process : %d\n", getppid() );

		printf( "\nchild process sent SIGKILL to parent process\n" );
		
		kill( getppid(), SIGKILL );

		printf( "child process is now an orphan process\n" );
		sleep( 3 );
		printf( "child, parent : %d, %d\n", getpid(), getppid() );
	}
	else{
		printf( "child process created\n" );
	}

	return 0;
}

/*
========================================================================================================
Output:

child process created
child process : 7446
parent process : 7445

child process sent SIGKILL to parent process
child process is now an orphan process
child, parent : 7446, 6505

========================================================================================================
*/

