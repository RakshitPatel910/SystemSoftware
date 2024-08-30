/*
========================================================================================================

Name: 9
Author: Rakshit Patel
Description: Write a program to print the following information about a given file.
a. inode
b. number of hard links
c. uid
d. gid
e. size
f. block size
g. number of blocks
h. time of last access
i. time of last modification
j. time of last change
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<sys/stat.h>

int main( int argc, char** argv ){
	if( argc < 2 ){
		std::cout << "invalid arguments" << std::endl;
		return 0;
	}
	
	struct stat s;
	int i = stat( argv[1], &s );

	if( i == -1 ){
	       	std::cout << "Error retrieving info!" << std::endl;
		return 0;
	}

	std::cout << "inode: " << s.st_ino << std::endl;
	std::cout << "no. of hard link: " << s.st_nlink << std::endl;
	std::cout << "uid: " << s.st_uid << std::endl;
	std::cout << "gid: " << s.st_gid << std::endl;
	std::cout << "size: " << s.st_size << std::endl;
	std::cout << "block size: " << s.st_blksize << std::endl;
	std::cout << "no. of blocks: " << s.st_blocks << std::endl;
	std::cout << "time of last access: " << s.st_atime << std::endl;
	std::cout << "time of last modification: " << s.st_mtime << std::endl;
	std::cout << "time of last change: " << s.st_ctime << std::endl;

	return 0;
}

/*
========================================================================================================
Output:

./a.out file2.txt
inode: 3815528
no. of hard link: 1
uid: 1000
gid: 1000
size: 40
block size: 4096
no. of blocks: 8
time of last access: 1724953022
time of last modification: 1724952960
time of last change: 1724952960


========================================================================================================
*/

