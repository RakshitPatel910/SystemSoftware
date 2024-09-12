/*
========================================================================================================

Name: 21
Author: Rakshit Patel
Description: Write a program, call fork and print the parent and child process id.
Date: 29th August, 2024

========================================================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<sys/resource.h>

int main(){
	int cpid = fork();

	if( cpid == 0 ){
		printf("From child process:\n" );
		printf("pid of child : %d\n", getpid() );
		printf("pid of parent : %d\n", getppid() );
	}
	else{
		printf("From parent process:\n" );
                printf("pid of child : %d\n", cpid );
                printf("pid of parent : %d\n", getpid() );
	}

	return 0;
}

/*
========================================================================================================
Output:

./a.out 
From parent process:
pid of child : 5165
pid of parent : 5164
From child process:
pid of child : 5165
pid of parent : 5164


========================================================================================================
*/

