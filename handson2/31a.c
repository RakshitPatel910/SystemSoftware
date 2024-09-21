/*
========================================================================================================
Name : 31
Author : Rakshit Patel
Description : Write a program to create a semaphore and initialize value to the semaphore.
	a. create a binary semaphore
	b. create a counting semaphore
Date: 20 Sept, 2024.
========================================================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

typedef union semun{
        int val;
        struct semid_ds *buf;
        unsigned short int *arr;
} semun;

int main(){
        semun bSem;
        key_t bKey = ftok(".", 3);
        int bID = semget(bKey, 1, IPC_CREAT | 0744);
        bSem.val = 1;
        printf("Binary semaphore created\n");
        semctl(bID, 0, SETVAL, bSem);

        semun cSem;
        key_t cKey = ftok(".", 4);
        int cID = semget(cKey, 1, IPC_CREAT | 0744);
        cSem.val = 10;
        printf("Counting semaphore created with size: %d\n", cSem.val);
        semctl(cID, 0, SETVAL, cSem);

        return 0;
}

/*
========================================================================================================

./a.out 
Binary semaphore created
Counting semaphore created with size: 10

========================================================================================================
*/
