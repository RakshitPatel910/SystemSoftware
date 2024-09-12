/*
========================================================================================================

Name: 3
Author: Rakshit Patel
Description: Write a program to create a file and print the file descriptor value. Use creat ( ) system call
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<fcntl.h>

int main( int argc, char** argv ){
	if( argc < 2 ){
		std::cout << "invalid arguments" << std::endl;
                return 0;
        }

	int v = creat( argv[1], 0644 );

	std::cout << "File descriptor of created file is : " << v << std::endl;

	return 0;
}

/*
========================================================================================================
Output:

./a.out tempfile.txt
File descriptor of created file is : 3

========================================================================================================
*/

