#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int f = open("12_file.txt", O_RDWR | O_CREAT, 0666);

    if (fd == -1) {
	std::cout << "Error in file opening." << std::endl;
        return 0;
    }

    int fl = fcntl(fd, F_GETFL);

    std::cout << "File descriptor flags:" << std::endl;

    if (fl & O_RDONLY) std::cout << "O_RDONLY" << std::endl;
    if (fl & O_WRONLY) std::cout << "O_WRONLY" << std::endl;
    if (fl & O_RDWR)   std::cout << "O_RDWR" << std::endl;
    if (fl & O_CREAT)  std::cout << "O_CREAT" << std::endl;
    if (fl & O_APPEND) std::cout << "O_APPEND" << std::endl;
    if (fl & O_TRUNC)  std::cout << "O_TRUNC" << std::endl;
    if (fl & O_EXCL)   std::cout << "O_EXCL" << std::endl;
    if (fl & O_NONBLOCK) std::cout << "O_NONBLOCK" << std::endl;
    if (fl & O_SYNC)   std::cout << "O_SYNC" << std::endl;

    close(f);

    return 0;
}

