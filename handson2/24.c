/*
========================================================================================================
Name : 24
Author : Rakshit Patel
Description : Write a program to create a message queue and print the key and message queue id.
Date: 19 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int fd = open("msgqueuefile", O_CREAT | O_RDWR, 0666);
    	close(fd);
    
    	key_t key = ftok("msgqueuefile", 'B');
    	int msgid = msgget(key, 0666 | IPC_CREAT);
    
    	printf("Message Queue Key: %d\n", key);
    	printf("Message Queue ID: %d\n", msgid);
    
    	msgctl(msgid, IPC_RMID, NULL);
    	
	return 0;
}

/*
========================================================================================================

./a.out 
Message Queue Key: 1107586790
Message Queue ID: 0

========================================================================================================
*/

