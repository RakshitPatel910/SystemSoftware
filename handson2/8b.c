/*
========================================================================================================
Name : 8b
Author : Rakshit Patel
Description : Write a separate program using signal system call to catch the following signals.
                b. SIGINT
Date: 16 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void sigint_handler(int signo) {
        printf("SIGINT (Interrupt) occured\n");
        exit(1);
}

int main() {
        signal(SIGINT, sigint_handler);
        printf("press crl + c\n");

	while( 1 );

	return 0;
}


/*
========================================================================================================
Output:

./a.out 
press crl + c
^CSIGINT (Interrupt) occured

========================================================================================================
*/

