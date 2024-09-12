/*
========================================================================================================

Name: 14
Author: Rakshit Patel
Description: Write a program to find the type of a file.
	a. Input should be taken from command line.
	b. program should be able to identify any type of a file.
Date: 29th August, 2024

========================================================================================================
*/


#include <iostream>    
#include <sys/stat.h>   
#include <sys/types.h>  

int main(int argc, char *argv[]) {
    struct stat s; 

    if (argc != 2) {
        std::cout << "invalid argument" << std::endl;
        return 1;
    }

    if (stat(argv[1], &s) == -1) {
	    std::cout << "Error retrieving file information" << std::endl;
        return 1;
    }

    if (S_ISREG(s.st_mode)) {
        std::cout << "regular file" << std::endl;
    } else if (S_ISDIR(s.st_mode)) {
        std::cout << "directory" << std::endl;
    } else if (S_ISCHR(s.st_mode)) {
        std::cout << "character device file" << std::endl;
    } else if (S_ISBLK(s.st_mode)) {
        std::cout << "block device file" << std::endl;
    } else if (S_ISFIFO(s.st_mode)) {
        std::cout << "FIFO" << std::endl;
    } else if (S_ISLNK(s.st_mode)) {
        std::cout << "symbolic link" << std::endl;
    } else if (S_ISSOCK(s.st_mode)) {
        std::cout << "socket" << std::endl;
    } else {
        std::cout << "file type not known" << std::endl;
    }

    return 0;
}

/*
========================================================================================================
Output:

./a.out file1.txt
regular file

========================================================================================================
*/

