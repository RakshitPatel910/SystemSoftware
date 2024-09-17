/*
========================================================================================================
Name : 8e
Author : Rakshit Patel
Description : Write a separate program using signal system call to catch the following signals.
                e. SIGINT(use setitimer system call)
Date: 16 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>

void sigalrm_handler(int signo) {
        printf("SIGINT (Alrm) occured\n");
        exit(1);
}

int main() {
        signal(SIGALRM, sigalrm_handler);
        
	struct itimerval t;
	t.it_value.tv_sec = 2;
	t.it_value.tv_usec = 0;
	t.it_interval.tv_sec = 0;
	t.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &t, NULL);
	
	pause();

        return 0;
}


/*
========================================================================================================
Output:

./a.out
SIGINT (Alrm) occured

========================================================================================================
*/

