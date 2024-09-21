/*
========================================================================================================
Name : 32c
Author : Rakshit Patel
Description : Write a program to implement semaphore to protect any critical section.
        c. protect multiple pseudo resources ( may be two) using counting semaphore
Date: 20 Sept, 2024.
========================================================================================================
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>

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

	sk = ftok(".", 333);
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
		s.val = 2;
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

	printf("Lock obtained!\n");

	printf("Inside Critical section");
	getchar();
	int d;
	int fd = open("./32c_ticket.txt", O_RDWR | O_CREAT, S_IRWXU);
	if (fd == -1) {
		perror("File open error!");
	}

	int n = read(fd, &d, sizeof(d));
	if (n == 0) {
		d = 1;
	} else {
		d += 1;
		lseek(fd, 0, SEEK_SET);
	}
	write(fd, &d, sizeof(d));
	printf("Ticket number is: %d\n", d);
	printf("Ticket number is stored in file\n");

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
Inside Critical section

./a.out 
Entering lock on critical section
Lock obtained!
Inside Critical section

./a.out
Entering lock on critical section



./a.out
Entering lock on critical section
Lock obtained!
Inside Critical section
Ticket number is: 1
Ticket number is stored in file

./a.out
Entering lock on critical section
Lock obtained!
Inside Critical section
Ticket number is: 2
Ticket number is stored in file

./a.out
Entering lock on critical section
Lock obtained!
Inside Critical section

========================================================================================================
*/

