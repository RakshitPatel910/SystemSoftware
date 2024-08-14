#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("12_file.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    std::cout << "File descriptor flags:" << std::endl;

    if (flags & O_RDONLY) std::cout << "O_RDONLY (read only)" << std::endl;
    if (flags & O_WRONLY) std::cout << "O_WRONLY (write only)" << std::endl;
    if (flags & O_RDWR)   std::cout << "O_RDWR (read and write)" << std::endl;
    if (flags & O_CREAT)  std::cout << "O_CREAT (create file if it does not exist)" << std::endl;
    if (flags & O_APPEND) std::cout << "O_APPEND (append to the end of file)" << std::endl;
    if (flags & O_TRUNC)  std::cout << "O_TRUNC (truncate file to zero length)" << std::endl;
    if (flags & O_EXCL)   std::cout << "O_EXCL (exclusive creation)" << std::endl;
    if (flags & O_NONBLOCK) std::cout << "O_NONBLOCK (non-blocking mode)" << std::endl;
    if (flags & O_SYNC)   std::cout << "O_SYNC (synchronous writes)" << std::endl;

    close(fd);
    return 0;
}

