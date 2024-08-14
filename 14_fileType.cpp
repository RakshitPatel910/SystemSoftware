#include <iostream>     // For std::cout
#include <sys/stat.h>   // For stat, S_ISREG, S_ISDIR, etc.
#include <sys/types.h>  // For file type macros

int main(int argc, char *argv[]) {
    struct stat s;  // Variable for storing file status information

    // Check if the user provided exactly one argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    }

    // Retrieve file status information
    if (stat(argv[1], &s) == -1) {
        std::perror("Error retrieving file information");
        return 1;
    }

    // Determine and print the file type
    if (S_ISREG(s.st_mode)) {
        std::cout << "regular file" << std::endl;
    } else if (S_ISDIR(s.st_mode)) {
        std::cout << "directory" << std::endl;
    } else if (S_ISCHR(s.st_mode)) {
        std::cout << "character device file" << std::endl;
    } else if (S_ISBLK(s.st_mode)) {
        std::cout << "block device file" << std::endl;
    } else if (S_ISFIFO(s.st_mode)) {
        std::cout << "FIFO (named pipe)" << std::endl;
    } else if (S_ISLNK(s.st_mode)) {
        std::cout << "symbolic link" << std::endl;
    } else if (S_ISSOCK(s.st_mode)) {
        std::cout << "socket" << std::endl;
    } else {
        std::cout << "unknown file type" << std::endl;
    }

    return 0;
}

