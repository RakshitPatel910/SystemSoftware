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
