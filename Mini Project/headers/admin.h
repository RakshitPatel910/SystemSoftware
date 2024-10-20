#ifndef ADMIN
#define ADMIN

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
#include <stdbool.h>

#include "../structures/users.h"
#include "./commonFunc.h"
#include "./const.h"

#define MAX_CLIENTS 10
#define MAX_MESSAGE_SIZE 256


bool handle_admin( int client_socket, struct User *admin );
int addEmployee( int client_socket );
int modifyCustEmp( int client_socket );
int manage_user_role( int client_socket );
int changePasswordAdmin( int client_socket, int admin_id );

int addEmployee( int client_socket ){
    printf("op 1\n");
    struct Employee emp;

    char read_buffer[1000], write_buffer[1000];  //, buffer[1000]
    int read_bytes, write_bytes;
    
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    write_bytes = send(client_socket, USERNAME, strlen(USERNAME), 0);
    read_bytes = recv(client_socket, &read_buffer, sizeof(read_buffer), 0);
    // printf("%s ", read_buffer);
    // read_bytes = recv(client_socket, &emp.username, sizeof(emp.username), 0);
    // read_bytes = recv(client_socket, &emp.username, 15, 0);
    strcpy(emp.username, read_buffer);
    printf("uname %s, %d\n", emp.username, read_bytes);

    memset(read_buffer, 0, sizeof(read_buffer));
    // memset(write_buffer, 0, sizeof(write_buffer));

    write_bytes = send(client_socket, ROLE, strlen(ROLE), 0);
    read_bytes = recv(client_socket, &read_buffer, sizeof(read_buffer), 0);
    emp.role = atoi( read_buffer );
    memset(read_buffer, 0, sizeof(read_buffer));


    write_bytes = send(client_socket, PASSWORD, strlen(PASSWORD), 0);
    read_bytes = recv(client_socket, &read_buffer, sizeof(read_buffer), 0);
    // printf("%s ", read_buffer);
    // read_bytes = recv(client_socket, &emp.password, sizeof(emp.password), 0);
    // read_bytes = recv(client_socket, &emp.password, 15, 0);
    strcpy(emp.password, read_buffer);
    printf("pass %s, %d\n", emp.password, read_bytes);



    // recv( client_socket, &emp, sizeof(emp), 0 );
    printf( "%d, %s, %s\n", emp.id, emp.username, emp.password );

    int total_emp_fd = open( "./dataBaseFiles/employee/totalEmp.txt", O_RDWR );
    int emp_list_fd = open( "./dataBaseFiles/employee/employee.txt", O_RDWR );

    printf( "%d, %d\n", total_emp_fd, emp_list_fd );
    int total_emp = 0;
    if( read( total_emp_fd, &total_emp, sizeof(total_emp) ) <= 0 ){
        printf("no entries\n");
        printf("%d\n", total_emp);
        total_emp = 0;

        emp.id = total_emp;
        for( int i = 0; i < 15; i++ ){
            emp.loanAssigned[i] = -1;
        }

        printf( "%d, %d, %s, %s", emp.id, emp.role, emp.username, emp.password );
        lseek( emp_list_fd, 0, SEEK_SET );
        write( emp_list_fd, &emp, sizeof(emp) );

        total_emp++;
        lseek( total_emp_fd, 0, SEEK_SET );
        write( total_emp_fd, &total_emp, sizeof(total_emp) );
    }
    else{
        printf("%d\n", total_emp);
        emp.id = total_emp;
        for( int i = 0; i < 15; i++ ){
            emp.loanAssigned[i] = -1;
        }

        printf( "%d, %d, %s, %s", emp.id, emp.role, emp.username, emp.password );
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

int modifyCustEmp( int client_socket ){
    int choice;
    recv(client_socket, &choice, sizeof(choice), 0);
    printf("choice val %d\n", choice);

    if (choice == 1) { // Modify Customer Details
        // int customer_id;
        // recv(client_socket, &customer_id, sizeof(customer_id), 0);

        // int customer_fd = open("./dataBaseFiles/customer/customer.txt", O_RDWR);
        // struct User customer;
        // lseek(customer_fd, sizeof(customer) * customer_id, SEEK_SET);
        // read(customer_fd, &customer, sizeof(customer));

        // printf("%d, %s, %s, %f\n", customer.id, customer.username, customer.password, customer.balance);

        // char new_username[50];
        // char new_password[50];
        // float new_balance;
        // recv(client_socket, new_username, sizeof(new_username), 0);
        // recv(client_socket, new_password, sizeof(new_password), 0);
        // recv(client_socket, &new_balance, sizeof(new_balance), 0);

        // strcpy(customer.username, new_username);
        // strcpy(customer.password, new_password);
        // customer.balance = new_balance;

        // lseek(customer_fd, sizeof(customer) * customer_id, SEEK_SET);
        // write(customer_fd, &customer, sizeof(customer));

        // close(customer_fd);

        // send(client_socket, "Customer details modified successfully", MAX_MESSAGE_SIZE, 0);
    } else if (choice == 2) { // Modify Employee Details
        int employee_id;
        recv(client_socket, &employee_id, sizeof(employee_id), 0);

        int employee_fd = open("./dataBaseFiles/employee/employee.txt", O_RDWR);
        struct Employee employee;

        printf( "size %ld\n", sizeof(employee) * employee_id );
        printf( "emp_id %d\n", employee_id );

        lseek(employee_fd, sizeof(employee) * employee_id, SEEK_SET);
        read(employee_fd, &employee, sizeof(employee));

        printf("%d, %s, %s\n", employee.id, employee.username, employee.password);

        char new_username[15];
        char new_password[15];
        // recv(client_socket, new_username, sizeof(new_username), 0);
        // recv(client_socket, new_password, sizeof(new_password), 0);
        recv( client_socket, &employee, sizeof(employee), 0 );

        // strcpy(employee.username, new_username);
        // strcpy(employee.password, new_password);
        printf("new emp %d, %s, %s\n", employee.id, employee.username, employee.password);

        lseek(employee_fd, sizeof(employee) * employee_id, SEEK_SET);
        write(employee_fd, &employee, sizeof(employee));

        close(employee_fd);

        send(client_socket, "Employee details modified successfully", MAX_MESSAGE_SIZE, 0);
    } else {
        send(client_socket, "Invalid choice", MAX_MESSAGE_SIZE, 0);
    }
            
}

int manage_user_role( int client_socket ){
    struct Employee emp;
    int read_bytes, write_bytes;
    char read_buffer[1000], write_buffer[1000], buffer[1000];

    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    strcpy(write_buffer, "Enter employee Id:");
    write_bytes = send( client_socket, write_buffer, sizeof(write_buffer), 0 );
    memset(write_buffer, 0, sizeof(write_buffer));

    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );
    int emp_id = atoi( read_buffer );

    int emp_list_fd = open( "./dataBaseFiles/employee/employee.txt", O_RDWR );

    apply_file_lock( emp_list_fd, LOCK_SHARED, sizeof(emp), sizeof(emp) * emp_id );

    lseek( emp_list_fd, sizeof(emp) * emp_id, SEEK_SET );
    read( emp_list_fd, &emp, sizeof(emp) );

    release_file_lock( emp_list_fd, sizeof(emp), sizeof(emp) * emp_id );

    if( emp.role == 0 ){
        // role is employee
        sprintf( write_buffer, "ID: %d, Role: Employee\nEnter new role (0 for employee and 1 for manager):\n", emp_id );
    }
    else if ( emp.role == 1){
        //role is manager
        sprintf( write_buffer, "ID: %d, Role: Manager\nEnter new role (0 for employee and 1 for manager):\n", emp_id );
    }
    
    write_bytes = send( client_socket, write_buffer, sizeof(write_buffer), 0 );
    memset(write_buffer, 0, sizeof(write_buffer));

    memset(read_buffer, 0, sizeof(read_buffer));
    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );
    emp.role = atoi( read_buffer );

    apply_file_lock( emp_list_fd, LOCK_EXCLUSIVE, sizeof(emp), sizeof(emp) * emp_id );

    lseek( emp_list_fd, sizeof(emp) * emp_id, SEEK_SET );
    write_bytes = write( emp_list_fd, &emp, sizeof(emp) );

    release_file_lock( emp_list_fd, sizeof(emp), sizeof(emp) * emp_id );

    if( write_bytes != -1 ){
        strcpy( write_buffer, "Role changed succesfully!\n" );
        send( client_socket, write_buffer, sizeof(write_buffer), 0 );
        recv( client_socket, read_buffer, sizeof(read_buffer), 0 );
    }

    return 0;

}

int changePasswordAdmin( int client_socket, int admin_id ){
    char read_buffer[1000], write_buffer[1000];
    int read_bytes, write_bytes;

    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    int admin_list_fd = open( "./dataBaseFiles/admin/admin.txt", O_RDWR );

    write_bytes = send( client_socket, NEW_PASSWORD, strlen(NEW_PASSWORD), 0 );

    read_bytes = recv( client_socket, read_buffer, sizeof(read_buffer), 0 );


    struct Admin admin;
    apply_file_lock( admin_list_fd, LOCK_EXCLUSIVE, sizeof(admin), sizeof(admin) *admin_id );

    lseek( admin_list_fd, sizeof(admin) * admin_id, SEEK_SET );
    read( admin_list_fd, &admin, sizeof(admin) );

    strcpy( admin.password, read_buffer );
    lseek( admin_list_fd, sizeof(admin) * admin_id, SEEK_SET );
    write_bytes = write( admin_list_fd, &admin, sizeof(admin) );

    release_file_lock( admin_list_fd, sizeof(admin), sizeof(admin) *admin_id );


    close( admin_list_fd );

    if( write_bytes == -1 ){
        strcpy( write_buffer, "Some error occured. Password change failed.\n" );
        write_bytes = send( client_socket, write_buffer, sizeof(write_buffer), 0 );
    }
    else{
        strcpy( write_buffer, "Password changed successfully.\n" );
        write_bytes = send( client_socket, write_buffer, sizeof(write_buffer), 0 );
    }

    recv( client_socket, read_buffer, sizeof(read_buffer), 0 );

    return 0;
}

bool handle_admin( int client_socket, struct User *admin ){
    char read_buffer[1000], write_buffer[1000];
    int read_bytes, write_bytes;

    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    printf("admin started\n");
    while( 1 ){
        write_bytes = send(client_socket, ADMINISTRATOR_MENU, strlen(ADMINISTRATOR_MENU), 0);
        if (write_bytes == -1) {
            perror("Writing admin menu\n");
            return 0;
        }

        memset(read_buffer, 0, sizeof(read_buffer));
        read_bytes = recv(client_socket, &read_buffer, sizeof(read_buffer), 0);

        int opt = atoi( read_buffer );
        // recv( client_socket, &opt, sizeof(opt), 0 );

        printf("opt val %d\n", opt);
        switch ( opt ){
            case 1 :   // Add New Bank Employee
                addEmployee( client_socket );
                break;
            case 2 :  // Modify Customer/Employee Details
                modifyCustEmp( client_socket );
                break;
            case 3 :  // Manage User Roles
                manage_user_role( client_socket );
                break;
            case 4 :  // Change Password
                changePasswordAdmin( client_socket, admin->id );
                break;
            case 5 :  // Logout
                strcpy( write_buffer, "#*#logout#*#" );
                send( client_socket, write_buffer, sizeof(write_buffer), 0 );
                memset(write_buffer, 0, sizeof(write_buffer));
                return true;
            
            case 6 : { // Exit

            }
            default :
                send(client_socket, "Invalid choice", MAX_MESSAGE_SIZE, 0);
                break;
            
        }
    
    }
    return false;
}


#endif