/*
========================================================================================================
Name : 30
Author : Rakshit Patel
Description : Write a program to create a shared memory.
	a. write some data to the shared memory
	b. attach with O_RDONLY and check whether you are able to overwrite.
	c. detach the shared memory
	d. remove the shared memory
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

	char* rdbuff;
	rdbuff = shmat( shmid, (void*) 0, SHM_RDONLY );

	printf("trying to overwrite with rdonly:\n");
	scanf("%[^\n]", rdbuff );

	printf("shared memory: %s\n", buff);

	printf("detaching from shared mem...\n");

	if(shmdt( buff ) == -1 ) printf("error detaching buff\n");
	if(shmdt( rdbuff ) == -1 ) printf("error detaching rdbuff\n");

	if(shmctl( shmid, IPC_RMID, NULL ) == -1) printf("error removing shared memory\n");
	else printf("shared memory removed\n");

	return 0;
}

/*
========================================================================================================

./a.out 
enter to write in shared memory:
message from 30.c
shared memory: message from 30.c
trying to overwrite with rdonly:
shared memory: message from 30.c
detaching from shared mem...
shared memory removed

========================================================================================================
*/

