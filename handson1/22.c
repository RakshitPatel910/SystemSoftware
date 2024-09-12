/*
========================================================================================================

Name: 22
Author: Rakshit Patel
Description: Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.
Date: 29th August, 2024

========================================================================================================
*/


#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main( int argc, char** argv ){
	if( argc < 2 ){
		printf("Enter file name\n");
		return 0;
	}

	int f = open( argv[1], O_CREAT | O_RDWR, 0644 );

	int cpid = fork();

	if( cpid == 0 ){
		sleep(1);
		char* buff = "Child : File Updated!!!\n";

        	write( f, buff, 24 );
	}
	else {
		char* buff = "Parent : File Updated!!!\n";

		write( f, buff, 26 );
	}

	return 0;
}	

/*
========================================================================================================
Output:

./a.out 22file.txt

cat 22file.txt
Parent : File Updated!!!
Child : File Updated!!!

========================================================================================================
*/

