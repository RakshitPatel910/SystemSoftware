/*
========================================================================================================
Name : 10b
Author : Rakshit Patel
Description : Write a separate program using sigaction system call to catch the following signals.
		b. SIGINT
Date: 17 Sept, 2024.
========================================================================================================
*/


#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void sigint_handler( int signo ){
	printf( "SIGINT (Interrupt generated) \n" );
	exit( 1 );
}

int main(){
	struct sigaction sigAct;

	sigAct.sa_handler = sigint_handler;
	sigemptyset( &sigAct.sa_mask );
	sigAct.sa_flags = 0;

	sigaction( SIGINT, &sigAct, NULL );

	printf("press ctrl + c to generate interrupt\n");

	while ( 1 );

	return 0;
}

/*
========================================================================================================
Output:

./a.out
press ctrl + c to generate interrupt
^CSIGINT (Interrupt generated) 

========================================================================================================
*/

