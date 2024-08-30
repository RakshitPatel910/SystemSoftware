/*
========================================================================================================

Name: 11
Author: Rakshit Patel
Description:Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
	a. use dup
	b. use dup2
	c. use fcntl 
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string>
#include<cstring>

int main( int argc, char** argv ){
        if( argc < 2 ){
                std::cout << "invalid arguments" << std::endl;
                return 0;
        }

	int f = open( argv[1], O_CREAT | O_WRONLY, 0644 );

	char o[50] = "original text for file 11_file.txt ";

	write( f, o, strlen(o) );

	int d1 = dup( f );
	std::cout<<d1<<" is the new fd using dup!"<<std::endl;

	char b1[50] = "text appended using fd from dup! ";

	write( d1, b1, strlen(b1) );

	int d2 =  dup2( f, 87 );
        std::cout<<d2<<" is the new fd using dup2!"<<std::endl;
        
        char b2[50] = "text appended using fd from dup2! ";
        
        write( d2, b2, strlen(b2) );
	
	int fc1 = fcntl( f, F_DUPFD );
        std::cout<<fc1<<" is the new fd using fcntl!"<<std::endl;

        char b3[50] = "text appended using fd from fcntl! ";

        write( fc1, b3, strlen(b3) );

	char b4[200];
	
	lseek( f, 0, SEEK_SET );

//	while( true ){
//		
//		int s = read( f, b4, 1);
//		if( s == 0 || s == -1 ) break;
//	}
//
//	write( 1, b4, strlen(b4) );

	return 0;

}

/*
========================================================================================================
Output:

./a.out 11_file.txt
4 is the new fd using dup!
87 is the new fd using dup2!
34 is the new fd using fcntl!

cat 11_file.txt 
original text for file 11_file.txt text appended using fd from dup! text appended using fd from dup2! text appended using fd from fcntl! 

========================================================================================================
*/
