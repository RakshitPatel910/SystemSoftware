/*
========================================================================================================
Name : 8a
Author : Rakshit Patel
Description : Write a separate program using signal system call to catch the following signals.
		a. SIGSEGV
Date: 16 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void sigsegv_handler(int signo) {
	printf("SIGSEGV (Segmentation fault) occured\n");
	exit(1);
}

void trigg_segfault() {
	int *ptr = NULL;
	*ptr = 60; 
}

int main() {
    	signal(SIGSEGV, sigsegv_handler);
    	trigg_segfault();
}


/*
========================================================================================================
Output:

./a.out
SIGSEGV (Segmentation fault) ocurred

========================================================================================================
*/
