/*
========================================================================================================
Name : 10c
Author : Himanshu Rawat
Description : Write a separate program using sigaction system call to catch the following signals.
		c. SIGFPE
Date: 16 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void sigfpe_handler(int signo) {
        printf("SIGFPE (floating point exception) occured\n");
        exit(1);
}

int main(){
	struct sigaction sigAct;

	sigAct.sa_handler = sigfpe_handler;
	sigemptyset( &sigAct.sa_mask );
	sigAct.sa_flags = 0;

	sigaction( SIGFPE, &sigAct, NULL );

	int x = 1/0;

	return 0;
}

/*
========================================================================================================
Output:

./a.out
SIGFPE (floating point exception) occured

========================================================================================================
*/

