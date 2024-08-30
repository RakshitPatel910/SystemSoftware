/*
========================================================================================================

Name: 26b
Author: Rakshit Patel
Description: Write a program to execute an executable program.
	a. use some executable program
	b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 29th August, 2024

========================================================================================================
*/


#include<stdio.h>
#include<unistd.h>

int main( int argc, char** argv ){
	if( argc < 2 ){
		printf("Enter file name!!!\n" );
		return 0;
	}

	execl( "/home/rakshit-patel/SystemSoftware/b.out", "b.out", argv[1], NULL );
	
	return 0;
}

/*
========================================================================================================
Output:

g++ 3.cpp -o b.out

./a.out file1.txt
File descriptor of created file is : 3

========================================================================================================
*/

