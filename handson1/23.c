/*
========================================================================================================

Name: 23
Author: Rakshit Patel
Description: Write a program to create a Zombie state of the running program.
Date: 29th August, 2024

========================================================================================================
*/


#include<stdio.h>
#include<unistd.h>

int main(){
	int p = fork();

	if( !p ){
		printf( "child process with pid : %d\n", getpid() );
	}
	else{
		printf( "Press enter\n " );
		getchar();
	}

	return 0;
}

/*
========================================================================================================
Output:

./a.out
Press enter
 child process with pid : 5376

========================================================================================================
*/

