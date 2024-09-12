/*
========================================================================================================

Name: 1b
Author: Rakshit Patel
Description: Create the following types of a files using (i) shell command (ii) system call
                a. soft link (symlink system call)
                b. hard link (link system call)
                c. FIFO (mkfifo Library Function or mknod system call)
Date: 29th August, 2024

========================================================================================================
*/


#include<iostream>
#include<unistd.h>

using namespace std;

int main( int argc, char** argv ){
        if( argc < 3 ){
                cout << "invalid arguments"<<endl;
                return 0;
        }

	int v = link( argv[1], argv[2] );
       	if( v == 0 ) cout << "Hard Link created successfully!!!" << endl;
	else cout << "Link creation failed!" << endl;

	return 0;	
}

/*
========================================================================================================
Output:

./a.out file1.txt hl_file1
Hard Link created successfully!!!

========================================================================================================
*/
