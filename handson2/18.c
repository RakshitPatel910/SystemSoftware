/*
========================================================================================================
Name : 18
Author : Rakshit Patel
Description : Write a program to find out total number of directories on the pwd. execute ls -l | grep ^d | wc ? Use only dup2.
Date: 17 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2], pipefd2[2];
    pid_t cid, cid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cid = fork();
    if (cid == 0) {
        // First child: grep
        cid2 = fork();
        if (cid2 == 0) {
            close(pipefd[1]);  // Close unused writing end of pipefd
            close(pipefd2[0]); // Close unused reading end of pipefd2

            dup2(pipefd[0], 0); // Redirect stdin to pipe reading end
            dup2(pipefd2[1], 1); // Redirect stdout to pipe writing end

            execlp("grep", "grep", "^d", NULL);
            perror("execlp grep");
            exit(EXIT_FAILURE);
        } else {
            // Parent of grep: ls
            close(pipefd[0]);  // Close unused reading end of pipefd
            close(pipefd2[0]); // Close unused reading end of pipefd2
            close(pipefd2[1]); // Close unused writing end of pipefd2

            dup2(pipefd[1], 1); // Redirect stdout to pipe writing end

            execlp("ls", "ls", "-l", NULL);
            perror("execlp ls");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        close(pipefd[0]);  // Close unused reading end of pipefd
        close(pipefd[1]);  // Close unused writing end of pipefd
        close(pipefd2[1]); // Close unused writing end of pipefd2

        // Redirect stdin to pipe reading end for wc
        dup2(pipefd2[0], 0);

        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    // Wait for all child processes
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}

/*
========================================================================================================

./a.out 
0

========================================================================================================
*/

