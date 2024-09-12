/*
========================================================================================================

Name: 10
Author: Rakshit Patel
Description: Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
	a. check the return value of lseek
	b. open the file with od and check the empty spaces in between the data.
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<unistd.h>
#include<fcntl.h>

int main( int argc, char** argv ){
        if( argc < 2 ){
                std::cout << "invalid arguments" << std::endl;
                return 0;
        }

	int f = open( "10_file.txt", O_CREAT | O_RDWR, 0644 );

	if( f == -1 ){
		std::cout << "File related error!" << std::endl;
		return 0;
	}

	char b[11] = "0123456789";

	int w = write( f, b, 10 );
	if( w == -1 ) {
		std::cout << "Writing error!" << std::endl;
		return 0;
	}

	int o = lseek( f, 10, SEEK_CUR );
	if( o == -1 ){
		std::cout << "lseek error!" << std::endl;
		return 0;
	}
	else std::cout<< "O/p of lseek: " << o << std::endl; 

	w = write( f, b, 10 );
	if( w == -1 ) {
		std::cout << "Writing2 error!" << std::endl;
		return 0;
	}

	lseek( f, 0, SEEK_SET );

	char buff[30];

	w = read( f, buff, 30);

	write(1, buff, 30);

	return 0;

}

/*
========================================================================================================
Output:

cat 10_file.txt 
01234567890123456789

./a.out 10_file.txt
O/p of lseek: 20

od -c 10_file.txt
0000000   0   1   2   3   4   5   6   7   8   9  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0   0   1   2   3   4   5   6   7   8   9
0000036

========================================================================================================
*/

