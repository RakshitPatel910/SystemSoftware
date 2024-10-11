#ifndef EMPLOYEE
#define EMPLOYEE

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

#include "../structures/users.h"
#include "./const.h"

#define MAX_CLIENTS 10
#define MAX_MESSAGE_SIZE 256

int handle_employee( int client_socket, struct User *employee );
int addCustomer( int client_socket );
int modifyCustomer( int client_socket );

int addCustomer( int client_socket ){
    struct Employee emp;

    recv( client_socket, &emp, sizeof(emp), 0 );

    int total_emp_fd = open( "./dataBaseFiles/employee/totalEmp.txt", O_RDWR );
    int emp_list_fd = open( "./dataBaseFiles/employee/employee.txt", O_RDWR );

    int total_emp = 0;
    if( read( total_emp_fd, &total_emp, sizeof(total_emp) ) <= 0 ){
        total_emp = 0;

        emp.id = total_emp;

        lseek( emp_list_fd, 0, SEEK_SET );
        write( emp_list_fd, &emp, sizeof(emp) );

        total_emp++;
        lseek( total_emp_fd, 0, SEEK_SET );
        write( total_emp_fd, &total_emp, sizeof(total_emp) );
    }
    else{
        emp.id = total_emp;

        if( total_emp > 50 ) return 0;

        lseek( emp_list_fd, sizeof(emp) * total_emp, SEEK_SET );
        write( emp_list_fd, &emp, sizeof(emp) );
    
        total_emp++;
        lseek( total_emp_fd, 0, SEEK_SET );
        write( total_emp_fd, &total_emp, sizeof(total_emp) );
    }

    close( total_emp_fd );
    close( emp_list_fd );

    return 0;
}

int handle_employee( int client_socket, struct User *employee ){
    while( 1 ){
        int opt;
        recv( client_socket, &opt, sizeof(opt), 0 );

        printf("opt val %d\n", opt);
        switch ( opt ){
            case 1 :   // Add New Bank Employee
                addCustomer( client_socket );
                break;
            case 2 :   // Modify Customer Details
                modifyCustomer( client_socket );
                break;
            case 3 : { // Process Loan Applications

            }
            case 4 : { // Approve/Reject Loans

            }
            case 5 : { // View Assigned Loan Applications

            }
            case 6 : { // Change Password

            }
            case 7 : { // Logout

            }
            case 8 : { // Exit

            }
            default :
                send(client_socket, "Invalid choice", MAX_MESSAGE_SIZE, 0);
                break;
            
        }
    
    }

    return 0;
}

#endif
