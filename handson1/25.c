/*
========================================================================================================

Name: 25
Author: Rakshit Patel
Description: Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call).
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int p1 = fork();

	if( !p1 ){
		sleep(2);
		printf("1st child\n");
	}
	else{
		int p2 = fork();

		if( !p2 ){
			sleep(3);
			printf("2nd child\n");
		}
		else{
			int p3 = fork();

			if( !p3 ){
				sleep(4);
				printf("3rd child\n");
			}
			else{
				printf("waiting for 2nd child\n");
				waitpid( p2, NULL, 0 );
			}
		}
	}

	return 0;
}

/*
========================================================================================================
Output:

./a.out
waiting for 2nd child
1st child
2nd child
   ---after parent process ended---
3rd child

========================================================================================================
*/


