/*
========================================================================================================

Name: 12
Author: Rakshit Patel
Description Write a program to find out the opening mode of a file. Use fcntl. 
Date: 29th August, 2024

========================================================================================================
*/

#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char** argv ){
        if( argc < 2 ){
                std::cout << "invalid arguments" << std::endl;
                return 0;
        }

	int f = open( argv[1], O_RDWR | O_CREAT, 0644 );

 	if (f == -1) {
		std::cout << "Error in file opening." << std::endl;
        	return 0;
   	 }

	int fl = fcntl(f, F_GETFL);
	std::cout << "File descriptor flags:" << std::endl;

	if (fl & O_RDONLY) std::cout << "read only" << std::endl;
	if (fl & O_WRONLY) std::cout << "write only" << std::endl;
	if (fl & O_RDWR)   std::cout << "both read and write" << std::endl;
	if (fl & O_CREAT)  std::cout << "created file" << std::endl;
	if (fl & O_APPEND) std::cout << "appended to file" << std::endl;
	if (fl & O_TRUNC)  std::cout << "truncated in file" << std::endl;
	if (fl & O_EXCL)   std::cout << "exclusive and created" << std::endl;
	if (fl & O_NONBLOCK) std::cout << "non blocking" << std::endl;
	if (fl & O_SYNC)   std::cout << "synchronized" << std::endl;

    	close(f);

   	return 0;
}

/*
========================================================================================================
Output:

./a.out 12_file.txt
File descriptor flags:
both read and write

========================================================================================================
*/

