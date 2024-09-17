/*
========================================================================================================
Name : 9
Author : Rakshit Patel
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 16 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void sigint_handler ( int signo ){
	printf( "SIGINT received\n" );
	signal( SIGINT, SIG_DFL );
}

int main(){
	signal( SIGINT, SIG_IGN );
	printf( "signal will be ignored for 10 sec\n" );

	sleep( 10 );

	signal( SIGINT, sigint_handler );
	printf( "default signal behaviour set\n" );

	sleep( 10 );

	return 0;
}

/*
========================================================================================================
Output:

./a.out 
signal will be ignored for 10 sec
^C^C^C^C^Cdefault signal behaviour set
^CSIGINT received

========================================================================================================
*/

