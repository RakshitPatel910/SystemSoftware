/*
========================================================================================================
Name : 20a
Author : Rakshit Patel
Description : Write two programs so that both can communicate by FIFO -Use two way communication.
Date: 18 Sept, 2024.
========================================================================================================
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
        char *s; // Data to be sent through the buffer
    int fd;  // File descriptor of the FIFO file
    long int size = 100;
    char *file = "./21a-fifo";
    mkfifo(file, S_IRWXU);
    while (1)
    {
        fd = open(file, O_WRONLY);
        if (fd == -1)
            perror("Error");
        else
        {
            printf("enter message:\n");
            int l = getline(&s, &size, stdin);
            write(fd, s, l);
            close(fd);
        }

        fd = open(file, O_RDONLY); // File descriptor of the FIFO file

        if (fd == -1)
            perror("Error");
        else
        {
            char buf;
            while (read(fd, &buf, 1) > 0)
                write(1, &buf, 1);
            write(1, "\n", 1);
            close(fd);
        }
    }

    return 0;
}

/*
========================================================================================================

./a.out 
enter message:
msg from a to b
msg from b to a

enter message:
bye to b 
bye to a


./b.out
msg from a to b

enter message:
msg from b to a
bye to b

enter message:
bye to a

========================================================================================================
*/

