/*
========================================================================================================
Name : 13
Author : Rakshit Patel
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
Date: 17 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void sigstop_handler(){
	printf("Received SIGSTOP");
}

int main(){
	printf( "Process running with pid : %d\n", getpid() );
	
	signal(SIGSTOP, sigstop_handler);

	sleep(20);

	return 0;
}

/*
========================================================================================================
Output:

Terminal 1:
./a.out
Process running with pid : 10287

[1]+  Stopped                 ./a.out

Terminal 2:
./b.out
Enter PID: 10287

========================================================================================================
*/

