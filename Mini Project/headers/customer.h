#ifndef CUSTOMER
#define CUSTOMER

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
#include "../structures/loan.h"
#include "../structures/feedback.h"
#include "./commonFunc.h"
#include "./const.h"

int handle_customer( int client_socket, struct User* user );
int viewBalance( int client_socket, int cust_id );
int depsitMoney( int client_socket, int cust_id );
int withdrawMoney( int client_socket, int cust_id );
int transferMoney( int client_socket, int cust_id );
int loanApplication( int client_socket, int cust_id );
int addFeedback( int client_socket, int cust_id );

int viewBalance( int client_socket, int cust_id ){
    char read_buffer[1000], write_buffer[1000];
    int read_bytes, write_bytes;

    int cust_list_fd = open( "../dataBaseFiles/customer/customer.txt", O_RDONLY );

    struct Customer customer;
    apply_file_lock( cust_list_fd, LOCK_SHARED, sizeof(customer), sizeof(customer) *cust_id );

    lseek( cust_list_fd, sizeof(customer) * cust_id, SEEK_SET );
    read( cust_list_fd, &customer, sizeof(customer) );

    release_file_lock( cust_list_fd, sizeof(customer), sizeof(customer) *cust_id );
    
    sprintf( write_buffer, "Balance: %f\n\n", customer.balance );
    write_bytes = send( client_socket, write_buffer, sizeof(write_buffer), 0 );

    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );

    close( cust_list_fd );

    return 0;
}

int depsitMoney( int client_socket, int cust_id ){
    char read_buffer[1000], write_buffer[1000];
    int read_bytes, write_bytes;

    int cust_list_fd = open( "../dataBaseFiles/customer/customer.txt", O_RDWR );

    write_bytes = send( cust_list_fd, DEPOSIT_AMOUNT, strlen(DEPOSIT_AMOUNT), 0 );
    
    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );
    float deposit_amount = atof( read_buffer );

    struct Customer customer;
    apply_file_lock( cust_list_fd, LOCK_EXCLUSIVE, sizeof(customer), sizeof(customer) *cust_id );

    lseek( cust_list_fd, sizeof(customer) * cust_id, SEEK_SET );
    read( cust_list_fd, &customer, sizeof(customer) );

    customer.balance += deposit_amount;
    lseek( cust_list_fd, sizeof(customer) * cust_id, SEEK_SET );
    write( cust_list_fd, &customer, sizeof(customer) );

    release_file_lock( cust_list_fd, sizeof(customer), sizeof(customer) *cust_id );
    
    sprintf( write_buffer, "Balance after deposit: %f\n\n", customer.balance );
    write_bytes = send( client_socket, write_buffer, sizeof(write_buffer), 0 );

    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );

    close( cust_list_fd );

    return 0;
}

int withdrawMoney( int client_socket, int cust_id ){
    char read_buffer[1000], write_buffer[1000];
    int read_bytes, write_bytes;

    int cust_list_fd = open( "../dataBaseFiles/customer/customer.txt", O_RDWR );

    struct Customer customer;
    apply_file_lock( cust_list_fd, LOCK_SHARED, sizeof(customer), sizeof(customer) *cust_id );

    lseek( cust_list_fd, sizeof(customer) * cust_id, SEEK_SET );
    read( cust_list_fd, &customer, sizeof(customer) );

    release_file_lock( cust_list_fd, sizeof(customer), sizeof(customer) *cust_id );

    write_bytes = send( cust_list_fd, WITHDRAW_AMOUNT, strlen(WITHDRAW_AMOUNT), 0 );
    
    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );
    float withdraw_amount = atof( read_buffer );

    if( withdraw_amount > customer.balance ){
        write_bytes = send( client_socket, INSUFFICIENT_BALANCE, strlen(INSUFFICIENT_BALANCE), 0 );

        read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );

        return 0;
    }
    else if( withdraw_amount < 0 ){
        write_bytes = send( client_socket, NEGATIVE_BALANCE, strlen(NEGATIVE_BALANCE), 0 );

        read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );

        return 0;
    }

    apply_file_lock( cust_list_fd, LOCK_EXCLUSIVE, sizeof(customer), sizeof(customer) *cust_id );

    customer.balance -= withdraw_amount;
    lseek( cust_list_fd, sizeof(customer) * cust_id, SEEK_SET );
    write( cust_list_fd, &customer, sizeof(customer) );

    release_file_lock( cust_list_fd, sizeof(customer), sizeof(customer) *cust_id );
    
    sprintf( write_buffer, "Balance after withdraw: %f\n\n", customer.balance );
    write_bytes = send( client_socket, write_buffer, sizeof(write_buffer), 0 );

    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );

    close( cust_list_fd );

    return 0;
}

int transferMoney( int client_socket, int cust_id ){
    char read_buffer[1000], write_buffer[1000];
    int read_bytes, write_bytes;

    int cust_list_fd = open( "../dataBaseFiles/customer/customer.txt", O_RDWR );

    struct Customer from_customer, to_customer;
    apply_file_lock( cust_list_fd, LOCK_SHARED, sizeof(from_customer), sizeof(from_customer) *cust_id );

    lseek( cust_list_fd, sizeof(from_customer) * cust_id, SEEK_SET );
    read( cust_list_fd, &from_customer, sizeof(from_customer) );

    release_file_lock( cust_list_fd, sizeof(from_customer), sizeof(from_customer) *cust_id );

    write_bytes = send( cust_list_fd, WHOM_TO_TRANSFER, strlen(WHOM_TO_TRANSFER), 0 );
    
    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );
    int to_cust_id = atoi( read_buffer );

    apply_file_lock( cust_list_fd, LOCK_SHARED, sizeof(to_customer), sizeof(to_customer) * to_cust_id );

    lseek( cust_list_fd, sizeof(to_customer) * to_cust_id, SEEK_SET );
    read( cust_list_fd, &to_customer, sizeof(to_customer) );

    release_file_lock( cust_list_fd, sizeof(from_customer), sizeof(from_customer) * to_cust_id );

    write_bytes = send( cust_list_fd, TRANSFER_AMOUNT, strlen(TRANSFER_AMOUNT), 0 );
    
    memset(read_buffer, 0, sizeof(read_buffer));
    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );
    float transfer_amount = atof( read_buffer );

    if( transfer_amount > from_customer.balance ){
        write_bytes = send( client_socket, INSUFFICIENT_BALANCE, strlen(INSUFFICIENT_BALANCE), 0 );

        read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );

        return 0;
    }
    else if( transfer_amount < 0 ){
        write_bytes = send( client_socket, NEGATIVE_BALANCE, strlen(NEGATIVE_BALANCE), 0 );

        read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );

        return 0;
    }

    apply_file_lock( cust_list_fd, LOCK_EXCLUSIVE, sizeof(from_customer), sizeof(from_customer) *cust_id );

    from_customer.balance -= transfer_amount;
    lseek( cust_list_fd, sizeof(from_customer) * cust_id, SEEK_SET );
    write( cust_list_fd, &from_customer, sizeof(from_customer) );

    release_file_lock( cust_list_fd, sizeof(from_customer), sizeof(from_customer) *cust_id );
    
    apply_file_lock( cust_list_fd, LOCK_EXCLUSIVE, sizeof(to_customer), sizeof(to_customer) *cust_id );

    to_customer.balance += transfer_amount;
    lseek( cust_list_fd, sizeof(to_customer) * to_cust_id, SEEK_SET );
    write( cust_list_fd, &to_customer, sizeof(to_customer) );

    release_file_lock( cust_list_fd, sizeof(from_customer), sizeof(from_customer) * to_cust_id );

    sprintf( write_buffer, "Balance after transfer: %f\n\n", from_customer.balance );
    write_bytes = send( client_socket, write_buffer, sizeof(write_buffer), 0 );

    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );

    close( cust_list_fd );

    return 0;
}

int loanApplication( int client_socket, int cust_id ){
    char read_buffer[1000], write_buffer[1000];
    int read_bytes, write_bytes;

    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    int cust_list_fd = open( "../dataBaseFiles/customer/customer.txt", O_RDWR );

    struct Customer customer;
    apply_file_lock( cust_list_fd, LOCK_EXCLUSIVE, sizeof(customer), sizeof(customer) * cust_id );

    lseek( cust_list_fd, sizeof(customer) * cust_id, SEEK_SET );
    read( cust_list_fd, &customer, sizeof(customer) );

    release_file_lock( cust_list_fd, sizeof(customer), sizeof(customer) * cust_id );


    if( customer.loanID > -1 ){
        write_bytes = send( client_socket, ALREADY_APPLIED, strlen(ALREADY_APPLIED), 0 );

        read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );
        int amount_requested = atof( read_buffer );

        close( cust_id );

        return 0;
    }


    write_bytes = send( client_socket, ASK_LOAN_AMOUNT, strlen(ASK_LOAN_AMOUNT), 0 );

    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );
    int amount_requested = atof( read_buffer );

    int loan_list_fd = open( "../dataBaseFiles/loan/loanList.txt", O_RDWR );
    int file_size = lseek( loan_list_fd, 0, SEEK_END );

    struct Loan loan;
    loan.amount = amount_requested;
    loan.custId = cust_id;
    loan.empId = -1;
    loan.loanId = file_size / sizeof(loan);
    loan.loanStatus = 0;


    apply_file_lock( loan_list_fd, LOCK_EXCLUSIVE, sizeof(loan), sizeof(loan) * loan.loanId );

    lseek( loan_list_fd, sizeof(loan) * loan.loanId, SEEK_SET );
    write( loan_list_fd, &loan, sizeof(loan) );

    release_file_lock( loan_list_fd, sizeof(loan), sizeof(loan) * loan.loanId );


    apply_file_lock( cust_list_fd, LOCK_EXCLUSIVE, sizeof(customer), sizeof(customer) * cust_id );

    customer.loanID = loan.loanId;
    lseek( cust_list_fd, sizeof(customer) * cust_id, SEEK_SET );
    write( cust_list_fd, &customer, sizeof(customer) );

    release_file_lock( cust_list_fd, sizeof(customer), sizeof(customer) * cust_id );


    write_bytes = send( client_socket, LOAN_APPL_SUCCESS, strlen(LOAN_APPL_SUCCESS), 0 );

    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );

    close( loan_list_fd );
    close( cust_list_fd );

    return 0;
}

int addFeedback( int client_socket, int cust_id ){
    char read_buffer[1000], write_buffer[1000];
    int read_bytes, write_bytes;

    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    write_bytes = send( client_socket, GIVE_FEEDBACK, strlen(GIVE_FEEDBACK), 0 );

    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );
    
    int feedback_list_fd = open( "../dataBaseFiles/feedback/feedback.txt", O_RDWR );
    int file_size = lseek( feedback_list_fd, 0, SEEK_END );

    struct Feedback feedback;
    feedback.reviewStatus = 0;
    feedback.custId = cust_id;
    feedback.feedbackId = file_size / sizeof(feedback);
    strcpy( feedback.feedback, read_buffer );

    apply_file_lock( feedback_list_fd, LOCK_EXCLUSIVE, sizeof(feedback), sizeof(feedback) * feedback.feedbackId );

    lseek( feedback_list_fd, sizeof(feedback) * feedback.feedbackId, SEEK_SET );
    write_bytes = write( feedback_list_fd, &feedback, sizeof(feedback) );

    release_file_lock( feedback_list_fd, sizeof(feedback), sizeof(feedback) * feedback.feedbackId );

    if( write_bytes == -1 ){
        strcpy( write_buffer, "There was some error sending feedback.\n" );
        write_bytes = send( client_socket, write_buffer, sizeof(write_buffer), 0 );

        recv( client_socket, &read_buffer, sizeof(read_buffer), 0 );

        close( feedback_list_fd );
    }

    write_bytes = send( client_socket, FDBCK_ADD_SUCC, strlen(FDBCK_ADD_SUCC), 0 );

    recv( client_socket, &read_buffer, sizeof(read_buffer), 0 );

    close( feedback_list_fd );

    return 0;
}

int handle_customer( int client_socket, struct User* user ){
    char read_buffer[1000], write_buffer[1000];
    int read_bytes, write_bytes;

    printf("customer started\n");
    while( 1 ){
        write_bytes = send(client_socket, MANAGER_MENU, strlen(MANAGER_MENU), 0);
        if (write_bytes == -1) {
            perror("Writing customer menu\n");
            return 0;
        }

        memset(read_buffer, 0, sizeof(read_buffer));
        read_bytes = recv(client_socket, &read_buffer, sizeof(read_buffer), 0);

        int opt = atoi( read_buffer );
        // recv( client_socket, &opt, sizeof(opt), 0 );

        printf("opt val %d\n", opt);
        switch ( opt ){
            case 1 :   // View Account Balance
                // actDeactCustomerAccount( client_socket );
                break;
            case 2 :  // Deposit Money
                // assignLoanApplication( client_socket );
                break;
            case 3 :  // Withdraw Money
                // reviewFeedback( client_socket );
                break;
            case 4 : { // Transfer Funds

            }
            case 5 : { // Apply for a Loan  

            }
            case 6 : { // Adding Feedback

            }
            case 7 : { // View Transaction History

            }
            case 8 : { // Change Password

            }
            case 9 : { // Logout

            }
            case 10 : { // Exit

            }
            default :
                send(client_socket, "Invalid choice", sizeof(write_buffer), 0);
                break;
            
        }
    
    }

    return 0;
}

#endif