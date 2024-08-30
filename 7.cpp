/*
========================================================================================================

Name: 7
Author: Rakshit Patel
Description: Write a program to copy file1 into file2 ($cp file1 file2).
Date: 29th August, 2024

========================================================================================================
*/


#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>

int main( int argc, char** argv ){
	int f1 = open( argv[1], O_CREAT | O_RDWR, 0644);
	int f2 = open( argv[2], O_CREAT | O_RDWR, 0644);
//	std::cout<<f1<<" "<<f2<<std::endl;

	char b1[21] = "file 1 before copy,\n";
	char b2[21] = "file 2 before copy,\n";

	std::cout<<"file1: ";
	ssize_t s1 = write( f1, b1, 20);
	std::cout<<"file2: ";
	ssize_t s2 = write( f2, b2, 20);
//	std::cout<<s1<<std::endl;

	write( 1, b1, 20 );
	write( 1, b2, 20 );

	lseek(f1, 0, SEEK_SET);

	s1 = read( f1 , b2, 20 );
//	std::cout<<s1<<std::endl;

	s1 = write( f2, b2, 20);

	lseek( f2, 0, SEEK_SET );

	char finalB[40] ={0};
	s1 = read( f2, finalB, 40);
//	std::cout<<s1<<std::endl;

	std::cout << std::endl << "After copy from file1 to file2, file2: \n" << std::endl;
	s1 = write( 1, finalB, 40);
	std::cout << std::endl;
//	std::cout<<s1<<std::endl;

	close(f1);
	close(f2);

	return 0;	
}

/*
========================================================================================================
Output:

./a.out file1.txt file2.txt
file 1 before copy,
file 2 before copy,
file1: file2: 
After copy from file1 to file2, file2: 

file 2 before copy,
file 1 before copy,

cat file1.txt
file 1 before copy,

cat file2.txt
file 2 before copy,
file 1 before copy,

========================================================================================================
*/
