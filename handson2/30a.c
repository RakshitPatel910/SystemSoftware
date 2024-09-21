/*
========================================================================================================
Name : 30a
Author : Rakshit Patel
Description : Write a program to create a shared memory.
	a. write some data to the shared memory
Date: 19 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main(){
	key_t key = ftok( ".", 2 );

	int shmid = shmget( key, 1024, 0774 | IPC_CREAT );

	char* buff;
	buff = shmat( shmid, (void*) 0, 0 );

	printf("enter to write in shared memory:\n");
	scanf("%[^\n]", buff );

	printf("shared memory: %s\n", buff);

	return 0;
}

/*
========================================================================================================

./a.out 
enter to write in shared memory:
message from 30a
shared memory: message from 30a

========================================================================================================
*/

