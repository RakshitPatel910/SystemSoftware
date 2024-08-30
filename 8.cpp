/*
========================================================================================================

Name: 8
Author: Rakshit Patel
Description: Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main( int argc, char** argv ){
        if( argc < 2 ){
                std::cout << "invalid arguments" << std::endl;
                return 0;
        }

	int f = open( argv[1], O_RDONLY );

	if( f == -1 ){
	       	std::cout<< "Error opening file!" << std::endl;
		return 0;
	}

	char b[100];
	int c = 0;
	while( true ){

		int w = read( f, b + c, 1 );

		if( w == -1 ){
		       	std::cout << "Error reading!" << std::endl;
			return 0;
		}

		if( b[c++] == '\n' ){
		       	write( 1, b, c );
			c = 0;
			getchar();
		}

		if( w == 0 ) break;
	}
	
	close(f);

	return 0;

}	

/*
========================================================================================================
Output:

cat file2.txt 
file 2 before copy,
file 1 before copy,

./a.out file2.txt
file 2 before copy,

file 1 before copy,


========================================================================================================
*/

