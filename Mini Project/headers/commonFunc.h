#ifndef COMMONFUNC
#define COMMONFUNC

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>

#include "../structures/users.h"
#include "../structures/transaction.h"

typedef enum {
    LOCK_SHARED = 1,
    LOCK_EXCLUSIVE = 2
} LockType;

int initialise_semphore(int ID, char *file_path);
bool lock_login_sem(struct sembuf *semOp, int sem_id);
bool unlock_login_sem(struct sembuf *semOp, int sem_id);

int initialise_semphore(int ID, char *file_path) {
    key_t sem_key = ftok(file_path, ID);
    union semun {
        int val;
    } semSet;

    int semctlStatus;
    int sem_id = semget(sem_key, 1, 0);
    if (sem_id == -1) {
        sem_id = semget(sem_key, 1, IPC_CREAT | 0700);
        if (sem_id == -1) {
            perror("Error while creating semaphore");
            _exit(1);
        }

        semSet.val = 1;
        semctlStatus = semctl(sem_id, 0, SETVAL, semSet);
        if (semctlStatus == -1) {
            perror("Error while initializing a binary sempahore");
            _exit(1);
        }
    }
    return sem_id;
}

bool lock_login_sem(struct sembuf *semOp, int sem_id) {
    semOp->sem_flg = SEM_UNDO;
    semOp->sem_op = -1;
    semOp->sem_num = 0;
    int semopStatus = semop(sem_id, semOp, 1);
    if (semopStatus == -1) {
        perror("Error locking login");
        return false;
    }
    return true;
}

bool unlock_login_sem(struct sembuf *semOp, int sem_id) {
    semOp->sem_op = 1;
    int semopStatus = semop(sem_id, semOp, 1);
    if (semopStatus == -1) {
        perror("Error unlocking login!");
        _exit(1);
    }
    return true;
}


void lock_file(int fd, LockType lock_type) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = (lock_type == LOCK_EXCLUSIVE) ? F_WRLCK : F_RDLCK;  // Write lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;        // Start of the file
    lock.l_len = 0;          // Lock the whole file

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to lock the file");
        exit(EXIT_FAILURE);
    }
}

void unlock_file(int fd) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_UNLCK;  // Unlock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;        // Start of the file
    lock.l_len = 0;          // Unlock the whole file

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to unlock the file");
        exit(EXIT_FAILURE);
    }
}

int apply_file_lock(int fd, LockType lock_type, size_t struct_size, off_t offset) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));

    lock.l_type = (lock_type == LOCK_EXCLUSIVE) ? F_WRLCK : F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = struct_size;

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to apply lock");
        return -1;
    }

    return 0;
}

int release_file_lock(int fd, size_t struct_size, off_t offset) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));

    lock.l_type = F_UNLCK; 
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = struct_size;

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to release lock");
        return -1;
    }

    return 0;
}

int addTransactionToCustomer( struct Customer* customer, struct Transaction* transaction ){
    int transaction_list_fd = open( "./dataBaseFiles/transaction/transaction.txt", O_RDWR );
    int file_size = lseek( transaction_list_fd, 0, SEEK_END );
    transaction->tID = file_size / sizeof(*transaction);

    close( transaction_list_fd );

    customer->transaction[customer->tp] = transaction->tID;
    customer->tp = (customer->tp + 1) % 15;
    
    int cust_list_fd = open( "./dataBaseFiles/customer/customer.txt", O_RDWR );

    apply_file_lock( cust_list_fd, LOCK_EXCLUSIVE, sizeof(*customer), sizeof(*customer) * customer->acc_no );
    // lock_file( cust_list_fd, LOCK_EXCLUSIVE );

    lseek( cust_list_fd, sizeof(*customer) * customer->acc_no, SEEK_SET );
    write( cust_list_fd, customer, sizeof(*customer) );

    release_file_lock( cust_list_fd, sizeof(*customer), sizeof(*customer) * customer->acc_no );
    // unlock_file( cust_list_fd );

    close( cust_list_fd );

    return 0;
}

int addTransaction(  struct Transaction* transaction ){
    int transaction_list_fd = open( "./dataBaseFiles/transaction/transaction.txt", O_RDWR );
    int file_size = lseek( transaction_list_fd, 0, SEEK_END );
    transaction->tID = file_size / sizeof(*transaction);


    apply_file_lock( transaction_list_fd, LOCK_EXCLUSIVE, sizeof(*transaction), sizeof(*transaction) * transaction->tID );
    // lock_file( transaction_list_fd, LOCK_EXCLUSIVE );

    lseek( transaction_list_fd, sizeof(*transaction) * transaction->tID, SEEK_SET );
    write( transaction_list_fd, transaction, sizeof(*transaction) );

    release_file_lock( transaction_list_fd, sizeof(*transaction), sizeof(*transaction) * transaction->tID );
    // unlock_file( transaction_list_fd );

    close( transaction_list_fd );

    return 0;
}

int admin_login( int client_socket, struct User *user, struct sembuf *sem_op, int *sem_id ){
    int admin_list_fd = open( "./dataBaseFiles/admin/admin.txt", O_RDONLY );

    struct Admin admin;
    int isValid = 0;

    lseek( admin_list_fd, 0, SEEK_SET );
    while ( read( admin_list_fd, &admin, sizeof(admin) ) > 0 ){
        if( strcmp(user->username, admin.username) == 0 && strcmp(user->password, admin.password) == 0 ){
            *sem_id = initialise_semphore( admin.id, "./dataBaseFiles/admin/admin.txt" );
            lock_login_sem( sem_op, *sem_id );

            isValid = 1;
            user->id = admin.id;

            break;
        }
    }

    if ( isValid ) {
        printf("Login successful\n");
        send( client_socket, &isValid, sizeof(isValid), 0 );
    } else {
        printf("Invalid username or password\n");
        send( client_socket, &isValid, sizeof(isValid), 0 );
    }
    
    close( admin_list_fd );

    return isValid;
}

int employee_login( int client_socket, struct User *user, int emp_type, struct sembuf *sem_op, int *sem_id ){
    int emp_list_fd = open( "./dataBaseFiles/employee/employee.txt", O_RDONLY );

    struct Employee emp;
    int isValid = 0;

    lseek( emp_list_fd, 0, SEEK_SET );
    while( read( emp_list_fd, &emp, sizeof(emp) ) > 0 ){
        if( strcmp(user->username, emp.username) == 0 && strcmp(user->password, emp.password) == 0 ){
            if( emp.role == emp_type ){
                *sem_id = initialise_semphore( emp.id, "./dataBaseFiles/employee/employee.txt" );
                lock_login_sem( sem_op, *sem_id );
                
                isValid = emp_type == 1 ? 2 : 3;
                user->id = emp.id;

                break;
            }
        }
    }

    if ( isValid ) {
        printf("Login successful\n");
        send( client_socket, &isValid, sizeof(isValid), 0 );
    } else {
        printf("Invalid username or password\n");
        send( client_socket, &isValid, sizeof(isValid), 0 );
    }
    
    close( emp_list_fd );

    return isValid;
}

int customer_login( int client_socket, struct User *user, struct sembuf *sem_op, int *sem_id ){
    int cust_list_fd = open( "./dataBaseFiles/customer/customer.txt", O_RDONLY );

    struct Customer customer;
    int isValid = 0;

    lseek( cust_list_fd, 0, SEEK_SET );
    while ( read( cust_list_fd, &customer, sizeof(customer) ) > 0 ){
        printf( "%s, %s\n", customer.username, customer.password );
        

        if( strcmp(user->username, customer.username) == 0 && strcmp(user->password, customer.password) == 0 ){
            if( customer.active == 0 ) break;

            *sem_id = initialise_semphore( customer.acc_no, "./dataBaseFiles/customer/customer.txt" );
            lock_login_sem( sem_op, *sem_id );
            isValid = 4;
            user->id = customer.acc_no;

            break;
        }
    }

    if ( isValid ) {
        printf("Login successful\n");
        send( client_socket, &isValid, sizeof(isValid), 0 );
    } else {
        printf("Invalid username or password\n");
        send( client_socket, &isValid, sizeof(isValid), 0 );
    }
    
    close( cust_list_fd );

    return isValid;
}

#endif