/*
========================================================================================================

Name: 1a
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

	int v { symlink( argv[1], argv[2] ) };

	if( v == 0 ) cout << "Soft Link created!!!" << endl;
	else cout << "Link Creation failed!" << endl;

	return 0;	
}

/*
========================================================================================================
Output:

./a.out file1.txt sf_file1
Soft Link created!!!

========================================================================================================
*/
