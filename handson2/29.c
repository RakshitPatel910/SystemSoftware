/*
========================================================================================================
Name : 29
Author : Rakshit Patel
Description : Write a program to remove the message queue.
Date: 19 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
	key_t key = ftok( ".", 1 );
	int msgid = msgget( key, 0666 | IPC_CREAT );

	int i = msgctl( msgid, IPC_RMID, NULL );

	if( i == -1 ){
		printf("error removing message queue\n");
		return 0;
	}

	printf("message queue removed\n");

	return 0;
}

/*
========================================================================================================

./a.out 
message queue removed

========================================================================================================
*/

