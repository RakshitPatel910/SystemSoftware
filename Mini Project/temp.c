#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

#include "./structures/users.h"
#include "./structures/transaction.h"

int main(){
    struct Customer c;
    struct Transaction t;

    // int total_emp_fd = open( "./dataBaseFiles/employee/totalEmp.txt", O_RDWR );
    // int emp_list_fd = open( "./dataBaseFiles/employee/employee.txt", O_RDWR );
    int cust_list_fd = open( "./dataBaseFiles/customer/customer.txt", O_RDONLY );

    lseek( cust_list_fd, sizeof(c)*0, SEEK_SET );
    read( cust_list_fd, &c, sizeof(c) );

    for( int i = 0; i < 15; i++ ){
        printf( "%d, ", c.transaction[i] );
    }
    printf("\n");

    for( int i = 0; i < 15; i++ ){
        if( c.transaction[(( c.tp - i + 15 ) % 15)] != -1 ) printf( "%d, %d\n", c.transaction[(( c.tp - i + 15 ) % 15)], i );
    }
    printf("\n");


    printf("tp: %d\n", c.tp );

    int transaction_list_fd = open( "./dataBaseFiles/transaction/transaction.txt", O_RDWR );
    char buffer[1000];

    while( read( transaction_list_fd, &t, sizeof(t) ) > 0 ){
        char trtype[14];
        if( t.transactionType == 1 ){
            strcpy( trtype, "DEPOSIT");
        }
        else if ( t.transactionType == 2 )
        {
            strcpy( trtype, "WITHDRAW");
        }
        else if ( t.transactionType == 3 )
        {
            strcpy( trtype, "TRANSFER(SEN)");
        }
        else if ( t.transactionType == 4 )
        {
            strcpy( trtype, "TRANSFER(REC)");
        }
        else if ( t.transactionType == 5 )
        {
            strcpy( trtype, "LOAN REC");
        }
        

        char timestr[25];
        struct tm *localTime = localtime(&t.transactionTime);
        strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localTime);
        // sprintf( buffer, "tID: %d | %s | amount: %.2f | time: %s\n", transaction.tID, trtype, transaction.amount, timestr );
        snprintf(buffer, sizeof(buffer), "tID: %d | %s | amount: %.2f | time: %s\n", t.tID, trtype, t.amount, timestr);
        printf("%s",buffer);
    }

    // read( emp_list_fd, &emp, sizeof(emp) );


}