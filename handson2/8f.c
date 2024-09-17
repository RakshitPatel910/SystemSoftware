/*
========================================================================================================
Name : 8f
Author : Rakshit Patel
Description : Write a separate program using signal system call to catch the following signals.
                f. SIGVTALRM (use setitimer system call)
Date: 16 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>

void sigvtint_handler(int signo) {
        printf("SIGVINT (Virtual Alarm) occured\n");
        exit(1);
}

int main() {
        signal(SIGVTALRM, sigvtint_handler);
        
	struct itimerval t;
	t.it_value.tv_sec = 2;
	t.it_value.tv_usec = 0;
	t.it_interval.tv_sec = 0;
	t.it_interval.tv_usec = 0;
	setitimer(ITIMER_VIRTUAL, &t, NULL);

	while( 1 );

        return 0;
}


/*
========================================================================================================
Output:

./a.out 
SIGVINT (Virtual Alarm) occured

========================================================================================================
*/

