/*
========================================================================================================
Name : 8d
Author : Rakshit Patel
Description : Write a separate program using signal system call to catch the following signals.
                d. SIGALRM
Date: 16 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void sigalrm_handler(int signo) {
        printf("SIGALRM (Alarm) occured\n");
        exit(1);
}

int main() {
        signal(SIGALRM, sigalrm_handler);
        
	alarm(3);
	pause();

        return 0;
}


/*
========================================================================================================
Output:

./a.out
SIGALRM (Alarm) occured

========================================================================================================
*/

