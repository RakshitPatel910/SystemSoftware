/*
========================================================================================================
Name : 8c
Author : Rakshit Patel
Description : Write a separate program using signal system call to catch the following signals.
                c. SIGFPE
Date: 16 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void sigfpe_handler(int signo) {
        printf("SIGFPE (floating point exception) occured\n");
        exit(1);
}

int main() {
        signal(SIGFPE, sigfpe_handler);
        
        int n = 1 / 0;

        return 0;
}


/*
========================================================================================================
Output:

./a.out 
SIGFPE (floating point exception) occured

========================================================================================================
*/
