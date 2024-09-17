/*
========================================================================================================
Name : 11
Author : Himanshu Rawat
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use sigaction system call.
Date: 17 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void sigint_handler ( int signo ){
        printf( "SIGINT received\n" );
        signal( SIGINT, SIG_DFL );
}

int main(){
        
	struct sigaction sigAct;

        sigAct.sa_handler = SIG_IGN;
        sigemptyset( &sigAct.sa_mask );
        sigAct.sa_flags = 0;
        sigaction( SIGINT, &sigAct, NULL );

        printf( "signal will be ignored for 10 sec\n" );
        sleep( 10 );


        sigAct.sa_handler = sigint_handler;
        sigemptyset( &sigAct.sa_mask );
        sigAct.sa_flags = 0;

        sigaction( SIGINT, &sigAct, NULL );

        printf( "default signal behaviour set\n" );
        sleep( 10 );

        return 0;
}

/*
========================================================================================================
Output:

./a.out 
signal will be ignored for 10 sec
^C^C^Cdefault signal behaviour set
^CSIGINT received

========================================================================================================
*/

