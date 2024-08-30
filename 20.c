/*
========================================================================================================

Name: 20
Author: Rakshit Patel
Description: Find out the priority of your running program. Modify the priority with nice command.
Date: 29th August, 2024

========================================================================================================
*/


#include<stdio.h>
#include<sys/resource.h>
#include<unistd.h>

int main(){
	int pri = getpriority( PRIO_PROCESS, 0 );

	printf( "Current priority of the process : %d\n", pri );

	pri = nice( 2 );

	printf( "Priority of the process after using nice : %d\n", pri );

	return 0;
}

/*
========================================================================================================
Output:

./a.out 
Current priority of the process : 0
Priority of the process after using nice : 2

========================================================================================================
*/
	
