/*
========================================================================================================

Name: 19
Author: Rakshit Patel
Description: Write a program to find out time taken to execute getpid system call. Use time stamp counter.
Date: 29th August, 2024

========================================================================================================
*/


#include<stdio.h>
#include<time.h>
#include<unistd.h>

unsigned long long rdtsc(){
	unsigned long long dst;
	__asm__ __volatile__("rdtsc":"=A" (dst));
}

int main(){
        unsigned long long int start, end;

        start = rdtsc();
        int getpid();
        end = rdtsc();

        unsigned long long int ti = (end - start)/2.4;

	printf( "time taken by getpid() function in  %lld nanosec\n", ti );

	return 0;
}

/*
========================================================================================================
Output:

./a.out
time taken by getpid() function in  25 nanosec

========================================================================================================
*/

