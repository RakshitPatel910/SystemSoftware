/*
========================================================================================================

Name: 4
Author: Rakshit Patel
Description: Write a program to open an existing file with read write mode. Try O_EXCL flag also.
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

	int v = open( argv[1], O_CREAT, O_RDWR );

	if( v == -1 ) std::cout << "File creation failed!" << std::endl;
	else std::cout << "File opened with RDWR with descriptor : " << v << std::endl;

	int v1 = open( argv[1], O_CREAT | O_EXCL, O_RDWR );

	if( v1 == -1 ) std::cout << "EXCL error!" << std::endl;
	else std::cout << "success!" << std::endl;

	return 0;
}

/*
========================================================================================================
Output:

./a.out 4_file
File opened with RDWR with descriptor : 3
EXCL error!

========================================================================================================
*/

