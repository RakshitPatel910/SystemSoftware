/*
========================================================================================================

Name: 26a
Author: Rakshit Patel
Description: Write a program to execute an executable program.
        a. use some executable program
        b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	execl("/bin/pwd","pwd", NULL); 

	return 0;
}

/*
========================================================================================================
Output:

./a.out
/home/rakshit-patel/SystemSoftware

========================================================================================================
*/

