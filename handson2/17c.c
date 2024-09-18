/*
========================================================================================================
Name : 17.c
Author : Rakshit Patel
Description : Write a program to execute ls -l | wc.
                c. Use fcntl
Date: 17 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(){
        int fd[2];
        int child_pid;
        pipe(fd);

        child_pid = fork();

        if (child_pid == 0) {
                close(0);
                fcntl(fd[0], F_DUPFD, 0);
                close(fd[1]);

                execl("/usr/bin/wc", "wc", NULL);               
                perror("execl");
                exit(1);
        }
        else {  
                close(1);
                fcntl(fd[1], F_DUPFD, 1);
                close(fd[0]);

                execl("/usr/bin/ls", "ls", "-l", NULL);
                perror("execl");
                exit(1);
        }

        return 0;
}

/*
========================================================================================================
Output:
./a.out
     33     290    2095

========================================================================================================
*/

