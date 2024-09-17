/*
========================================================================================================
Name : 10a
Author : Rakshit Patel
Description : Write a separate program using sigaction system call to catch the following signals.
		a. SIGSEGV
Date: 16 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigsegv_handler( int signo ){
	printf( "SIGSEGV (segmentation fault) occured\n" );
	exit( 1 );
}

int main(){
	struct sigaction sigAct;

	sigAct.sa_handler = sigsegv_handler;
	sigemptyset( &sigAct.sa_mask );
	sigAct.sa_flags = 0;

	sigaction( SIGSEGV, &sigAct, NULL );

	int *p = NULL;
	*p = 60;

	return 0;
}

/*
========================================================================================================
Output:

./a.out
SIGSEGV (segmentation fault) occured

========================================================================================================
*/

