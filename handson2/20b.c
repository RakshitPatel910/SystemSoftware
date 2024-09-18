/*
========================================================================================================
Name : 20b
Author : Rakshit Patel
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 18 Sept, 2024.
========================================================================================================
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    const char *fifoPath = "./20-fifo";

    while (1) {
        int fd = open(fifoPath, O_RDONLY);

        char buf[100];
        ssize_t bytesRead = read(fd, buf, sizeof(buf) - 1);
        if (bytesRead > 0) {
            buf[bytesRead] = '\0'; 
            if (strcmp(buf, "exit") == 0) { 
                close(fd);
                break; 
            }
            write(1, buf, bytesRead); 
            write(1, "\n", 1);
        }

        close(fd);
    }

    return 0;
}

/*
========================================================================================================

./a.out
Enter message (empty to exit):
hi
Enter message (empty to exit):
2nd msg
Enter message (empty to exit):


./b.out 
hi


2nd msg



========================================================================================================
*/

