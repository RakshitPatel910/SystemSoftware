/*
========================================================================================================
Name : 26
Author : Rakshit Patel
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 19 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

struct mesg_buffer {
    	long mesg_type;
    	char mesg_text[100];
};

int main() {
    	key_t key = ftok(".", 1);
    	int msgid = msgget(key, 0666 | IPC_CREAT); // Create or get the message queue

    	struct mesg_buffer message;

    	printf("enter msgtype:\n");
    	scanf("%ld", &message.mesg_type);
    	printf("enter data: \n");
    	getchar();
    	fgets(message.mesg_text, 100, stdin);
    	msgsnd(msgid, &message, sizeof(message), 0);
    	return 0;
}

/*
========================================================================================================

ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x01046ee6 1          rakshit-pa 666        0            0           
0x01045b7b 2          rakshit-pa 666        448          4  

./a.out
enter msgtype:
1
enter data:


./a.out
enter msgtype:
2
enter data:

ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x01046ee6 1          rakshit-pa 666        0            0
0x01045b7b 2          rakshit-pa 666        672          6

========================================================================================================
*/
