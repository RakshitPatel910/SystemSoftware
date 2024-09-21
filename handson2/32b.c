/*
========================================================================================================
Name : 32b
Author : Rakshit Patel
Description : Write a program to implement semaphore to protect any critical section.
        b. protect shared memory from concurrent write access
Date: 19 Sept, 2024.
========================================================================================================
*/


#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>

void main() {
	key_t k = ftok(".", 666);
	int id = shmget(k, 1024, IPC_CREAT | 0744);
	char *p = shmat(id, NULL, 0);
	key_t sk;
	int si, cs, os;

	union semun {
		int val;
		struct semid_ds *buf;
		unsigned short *array;
		struct seminfo *__buf;
	} s;

	sk = ftok(".", 332);
	if (sk == -1) {
		perror("Key error!");
		_exit(1);
	}

	si = semget(sk, 1, 0);
	if (si == -1) {
		si = semget(sk, 1, IPC_CREAT | 0700);
		if (si == -1) {
			perror("Semaphore creation error!");
			_exit(1);
		}
		s.val = 1;
		cs = semctl(si, 0, SETVAL, s);
		if (cs == -1) {
			perror("Semaphore init error!");
			_exit(1);
		}
	}

	struct sembuf op;
	op.sem_num = 0;
	op.sem_flg = 0;

	printf("Entering lock on critical section\n");

	op.sem_op = -1;
	os = semop(si, &op, 1);
	if (os == -1) {
		perror("Semaphore operation error!");
		_exit(1);
	}

	printf("Lock obtained!\nEntering critical section!\n");
	printf("Write in shared memory\n");
	scanf("%[^\n]", p);
	printf("Data from shared memory: %s\n", p);
	printf("Exiting critical section!\n");

	op.sem_op = 1;
	os = semop(si, &op, 1);
	if (os == -1) {
		perror("Semaphore operation error!");
		_exit(1);
	}
}


/*
========================================================================================================

./a.out
Entering lock on critical section
Lock obtained!
Entering critical section!
Write in shared memory
hi


./a.out
Entering lock on critical section



========================================================================================================
*/

