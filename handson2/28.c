/*
========================================================================================================
Name : 28
Author : Rakshit Patel
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 19 Sept, 2024.
========================================================================================================
*/

#include <sys/msg.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <time.h>

int main(){
	key_t key = ftok( ".", 1 );
	int msgid = msgget( key, 0666 | IPC_CREAT );

	struct msqid_ds mqinfo;
	msgctl( msgid, IPC_STAT, &mqinfo );

	struct ipc_perm mqperm = mqinfo.msg_perm;

	printf("permission %d\n", mqperm.mode );

	mqinfo.msg_perm.mode = 0666;
	msgctl( msgid, IPC_SET, &mqinfo );

	mqperm = mqinfo.msg_perm;
	printf("permission %d\n", mqperm.mode );

	return 0;
}

/*
========================================================================================================

./a.out 
permission 438
permission 511

========================================================================================================
*/


