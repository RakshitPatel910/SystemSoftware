/*
========================================================================================================

Name: 24
Author: Rakshit Patel
Description: Write a program to create an orphan process.
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	int p = fork();

	if( !p ){
		printf("pid of Parent process before sleep : %d\n", getppid() );

		sleep(4);

		printf("pid of Parent process after sleep : %d\n", getppid() );
	}
	else{
		sleep(1);
	}

	return 0;
}

/*
========================================================================================================
Output:

./a.out
pid of Parent process before sleep : 5419
         ---after 4 sec---
pid of Parent process after sleep : 1711
========================================================================================================
*/


