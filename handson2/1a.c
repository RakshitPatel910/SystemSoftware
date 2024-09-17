/*
========================================================================================================
Name : 1a
Author : Rakshit Patel
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
 		a. ITIMER_REAL
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<sys/time.h>
#include<signal.h>
#include<unistd.h>

void handle_alarm(int sig) {
    printf("ITIMER_REAL timer expired\n");
}

int main(){
	struct itimerval t;

	t.it_value.tv_sec = 10;
	t.it_value.tv_usec = 10;

	t.it_interval.tv_sec = 10;
	t.it_interval.tv_usec = 10;
	
	signal( SIGALRM, handle_alarm );

	int i = setitimer( ITIMER_REAL, &t, NULL );

	if( i == -1 ){
		printf("error");
		return 0;
	}

	pause();

	return 0;
}

/*
========================================================================================================

Output:
./a.out
ITIMER_REAL timer expired

==============================================================================================
==========

*/
