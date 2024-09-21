/*
========================================================================================================
Name : 27b
Author : Rakshit Patel
Description : Write a program to receive messages from the message queue.
        a. with IPC_NOWAIT as a flag
Date: 19 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<sys/msg.h>
#include<sys/ipc.h>

struct msg_buffer{
        long msg_type;
        char msg_text[100];
};      

int main(){
        struct msg_buffer msg;
        
        key_t key = ftok(".", 1);
        int msgid = msgget( key, 0666 | IPC_CREAT );
        
        printf("enter message type\n");
        scanf( "%ld", &msg.msg_type );
        
        int s = msgrcv( msgid, &msg, sizeof(msg), msg.msg_type, IPC_NOWAIT );
        
        if( s <= 0 ) printf("no message\n");
        else printf("message : %s\n", msg.msg_text );
        
        return 0;
}

/*
========================================================================================================

./a.out
enter message type
no message

========================================================================================================
*/
