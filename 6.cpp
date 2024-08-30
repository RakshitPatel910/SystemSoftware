/*
========================================================================================================

Name: 6
Author: Rakshit Patel
Description: Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 29th August, 2024

========================================================================================================
*/


#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstring>

int main() {
    char b[20];

    ssize_t s = read(0, b, 20);
    if (s == -1) {
        std::cout << "Reading failed!" << std::endl;
        //std::cerr << "Error: " << strerror(errno) << std::endl;
        return 1;
    } else {
        std::cout << s << " bytes were read!" << std::endl;
    }

    s = write(1, b, 20);
    if (s == -1) {
        std::cout << "Writing failed!" << std::endl;
        //std::cerr << "Error: " << strerror(errno) << std::endl;
        return 1;
    }

    return 0;
}

/*
========================================================================================================
Output:

./a.out
text for reading!!
19 bytes were read!
text for reading!!

========================================================================================================
*/

