/*
========================================================================================================
Name : 25
Author : Rakshit Patel
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
	a. access permission
	b. uid, gid
	c. time of last message sent and received
	d. time of last change in the message queue
	d. size of the queue
	f. number of messages in the queue
	g. maximum number of bytes allowed
	h. pid of the msgsnd and msgrcv
Date: 19 Sept, 2024.
========================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(){
	key_t key = ftok("msgqueuefile", 1);
    	int msgid = msgget(key, 0666 | IPC_CREAT);

    	struct msqid_ds buf;
    	msgctl(msgid, IPC_STAT, &buf);

    	struct ipc_perm msg_perm = buf.msg_perm; // Ownership and permissions
    	time_t msg_stime = buf.msg_stime;        // Time of last msgsnd
    	time_t msg_rtime = buf.msg_rtime;        // Time of last msgrcv
    	time_t msg_ctime = buf.msg_ctime;        // Time of last modification
    	unsigned long msg_cbytes = buf.msg_cbytes; // Number of bytes in queue
    	msgqnum_t msg_qnum = buf.msg_qnum;       // Number of messages in queue
    	msglen_t msg_qbytes = buf.msg_qbytes;    // Maximum bytes in queue
    	pid_t msg_lspid = buf.msg_lspid;         // PID of last msgsnd
    	pid_t msg_lrpid = buf.msg_lrpid;         // PID of last msgrcv

    	printf("Access Permission: %o\n", msg_perm.mode);
    	printf("UID: %d, GID: %d\n", msg_perm.uid, msg_perm.gid);
    	printf("Time of Last Message Sent: %ld\n", msg_stime);
    	printf("Time of Last Message Received: %ld\n", msg_rtime);
    	printf("Time of Last Change: %ld\n", msg_ctime);
    	printf("Number of Bytes in Queue: %ld\n", msg_cbytes);
    	printf("Number of Messages in Queue: %ld\n", msg_qnum);
    	printf("Maximum Number of Bytes Allowed: %ld\n", msg_qbytes);
    	printf("PID of Last msgsnd: %d\n", msg_lspid);
    	printf("PID of Last msgrcv: %d\n", msg_lrpid);

    	return 0;
}

/*
========================================================================================================

./a.out 
Access Permission: 666
UID: 1000, GID: 1000
Time of Last Message Sent: 0
Time of Last Message Received: 0
Time of Last Change: 1726724952
Number of Bytes in Queue: 0
Number of Messages in Queue: 0
Maximum Number of Bytes Allowed: 16384
PID of Last msgsnd: 0
PID of Last msgrcv: 0

========================================================================================================
*/

