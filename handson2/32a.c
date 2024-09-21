/*
========================================================================================================
Name : 32a
Author : Rakshit Patel
Description : Write a program to implement semaphore to protect any critical section.
	a. rewrite the ticket number creation program using semaphore
Date: 19 Sept, 2024.
========================================================================================================
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>

typedef union semun{
        int val;
        struct semid_ds *buf;
        unsigned short int *arr;
        struct seminfo *__buf;
} semun;

int main(){
        semun arg;
        key_t key = ftok(".", 331);
        int semid = semget(key, 1, 0);
        if (semid == -1){
                semid = semget(key, 1, IPC_CREAT | 0700);
                arg.val = 1;
                semctl(semid, 0, SETVAL, arg);
        }

        struct sembuf s;
        s.sem_num = 0;
        s.sem_flg = 0;

        printf("Entering critical zone\n");
        s.sem_op = -1;
        semop(semid, &s, 1);

        printf("Inside critical section\n");
        getchar();
        int data;
        int fd = open("./32_ticket.txt", O_RDWR | O_CREAT, S_IRWXU);
        if (fd == -1){
                perror("Error while opening file!");
                return 0;
        }

        int n = read(fd, &data, sizeof(data));
        if (n == 0) data = 1;
        else { data += 1; lseek(fd, 0, SEEK_SET); }
        write(fd, &data, sizeof(data));
        printf("Ticket number: %d\n", data);
        printf("Ticket number stored in file\n");

        printf("Out of critical zone\n");
        s.sem_op = 1;
        semop(semid, &s, 1);
        return 0;
}

/*
========================================================================================================

./a.out
Entering critical zone
Inside critical section

Ticket number: 1
Ticket number stored in file
Out of critical zone

./a.out
Entering critical zone
Inside critical section

Ticket number: 2
Ticket number stored in file
Out of critical zone

========================================================================================================
*/

