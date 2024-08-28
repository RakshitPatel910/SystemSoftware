#include<stdio.h>
#include<unistd.h>
#include<sys/resource.h>

int main(){
	int pri = getpriority( PRIO_PROCESS, 0 );

//	printf("Process ID : %d\n", pri );

	int cpri = fork();

	printf("Process ID : %d\n", getpid() );	

	return 0;
}
