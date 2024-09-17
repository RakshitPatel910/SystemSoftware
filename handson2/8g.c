/*
========================================================================================================
Name : 8g
Author : Rakshit Patel
Description : Write a separate program using signal system call to catch the following signals.
                g. SIGPROF (use setitimer system call)
Date: 16 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>

void sigprof_handler(int signo) {
        printf("SIGPROF (Profiling timer alarm) occured\n");
        exit(1);
}

int main() {
        signal(SIGPROF, sigprof_handler);
        
	struct itimerval t;
	t.it_value.tv_sec = 2;
	t.it_value.tv_usec = 0;
	t.it_interval.tv_sec = 0;
	t.it_interval.tv_usec = 0;
	setitimer(ITIMER_PROF, &t, NULL);

	while( 1 );
}


/*
========================================================================================================
Output:

./a.out 
SIGPROF (Profiling timer alarm) occured

========================================================================================================
*/

