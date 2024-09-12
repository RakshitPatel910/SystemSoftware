/*
========================================================================================================

Name: 1c
Author: Rakshit Patel
Description: Create the following types of a files using (i) shell command (ii) system call
                a. soft link (symlink system call)
                b. hard link (link system call)
                c. FIFO (mkfifo Library Function or mknod system call)
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<sys/stat.h>

using namespace std;

int main ( int argc, char** argv ) {
	if( argc < 2 ){
                cout << "invalid arguments"<<endl;
                return 0;
        }

	int v { mknod( "fifo_file", 755, 0 ) };

	if( v == 0 ) std::cout << "FIFO created succesfully!!!" << std::endl;
       	else std::cout << "FIFO creation failed!" << std::endl;

	return 0;	
}

/*
========================================================================================================
Output:

./a.out file1.txt fifo_file1
FIFO created succesfully!!!

========================================================================================================
*/

