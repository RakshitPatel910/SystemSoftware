/*
========================================================================================================
Name : 19
Author : Rakshit Patel
Description : Create a FIFO file by
	a. mknod command
	b. mkfifo command
	c. use strace command to find out, which command (mknod or mkfifo) is better.
	c. mknod system call
	d. mkfifo library function
Date: 18 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <sys/stat.h>

int main(){

	if( mknod( "./maknod_syscall", S_IFIFO | 0666, 0 ) == 0 ){
		printf(" fifo created using maknod syscall\n");
        }

	if( mkfifo( "./makefifo_libfunc", 0666 ) == 0 ){
		printf(" fifo created using makefifo lib func\n");
	}

	return 0;
}

/*
========================================================================================================

./a.out
 fifo created using maknod syscall
 fifo created using makefifo lib func

========================================================================================================
*/

