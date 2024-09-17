/*
========================================================================================================
Name : 1b
Author : Rakshit Patel
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
                b. ITIMER_VIRTUAL
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<sys/time.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void handle_alarm(int sig) {
    printf("ITIMER_VIRTUAL timer expired\n");
}


int main(){
	struct itimerval t;

	t.it_value.tv_sec = 10;
	t.it_value.tv_usec = 10;

	signal( SIGVTALRM, handle_alarm );

	int i = setitimer( ITIMER_VIRTUAL, &t, NULL );

	if( i == -1 ){
		printf("error");
		return 0;
	}

	while( 1 );

	return 0;
}

/*
========================================================================================================

Output:
./a.out 
ITIMER_VIRTUAL timer expired

==============================================================================================
==========

*/
