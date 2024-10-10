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

#define MAX_CLIENTS 10
#define MAX_MESSAGE_SIZE 256

struct User {
    char username[50];
    char password[50];
};

struct Employee {
    int id;
    char username[15];
    char password[15];
};

int handle_login( int client_socket, struct User *user ){
    int users_file_fd = open( "users.txt", O_RDWR );
    int total_user_fd = open( "totalClients", O_RDWR );
    if ( users_file_fd == -1 || total_user_fd == -1 ) {
        perror("open");
        return 1;
    } 
    
    struct User user_info;
    
    int tu;
    read( total_user_fd, &tu, sizeof(tu) );


    // tu = 2;
    // tu = tu + 1;
    // lseek( total_user_fd, 0 , SEEK_SET );
    // write( total_user_fd, &tu, sizeof(tu) );
    // printf( "%d, %ld\n", tu, sizeof(*user) * tu );

    // int l = lseek( users_file_fd, sizeof(*user) * tu , SEEK_SET );
    // int l = lseek( users_file_fd, 0 , SEEK_SET );
    
    // write( users_file_fd, user, sizeof(user_info) );

    lseek( users_file_fd, 0 , SEEK_SET );
    // printf("%d\n",l);
    int isValid = 0;
    printf( "%s\n", user->username );
    printf( "%s\n", user->password );
    while( read( users_file_fd, &user_info, sizeof(user_info) ) > 0 ){
        
        printf( "%s\n", user_info.username );
        printf( "%s\n", user_info.password );

        if( strcmp(user->username, user_info.username) == 0 && strcmp(user->password, user_info.password) == 0){
            isValid = 1;
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

    close( users_file_fd );
    close( total_user_fd );

    return isValid;
}

int addEmployee( int client_socket ){
    printf("op 1\n");
    struct Employee emp;

    recv( client_socket, &emp, sizeof(emp), 0 );
    printf( "%d, %s, %s\n", emp.id, emp.username, emp.password );

    int total_emp_fd = open( "./dataBaseFiles/employee/totalEmp.txt", O_RDWR );
    int emp_list_fd = open( "./dataBaseFiles/employee/employee.txt", O_RDWR );

    printf( "%d, %d\n", total_emp_fd, emp_list_fd );
    int total_emp = 0;
    if( read( total_emp_fd, &total_emp, sizeof(total_emp) ) <= 0 ){
        printf("no entries\n");
        printf("%d\n", total_emp);
        total_emp = 0;

        // struct Employee employee = {
        //     .id = total_emp,
        //     .username = emp.username,
        //     .password = emp.password
        // };
        // memcpy(employee.username, emp.username, sizeof(employee.username));
        // memcpy(employee.password, emp.password, sizeof(employee.password));
        emp.id = total_emp;

        printf( "%d, %s, %s", emp.id, emp.username, emp.password );
        lseek( emp_list_fd, 0, SEEK_SET );
        write( emp_list_fd, &emp, sizeof(emp) );

        total_emp++;
        lseek( total_emp_fd, 0, SEEK_SET );
        write( total_emp_fd, &total_emp, sizeof(total_emp) );
    }
    else{
        printf("%d\n", total_emp);
        // struct Employee employee = {
        //     total_emp,
        //     *emp.username,
        //     *emp.password
        // };
        emp.id = total_emp;

        if( total_emp > 50 ) return 0;

        printf( "%d, %s, %s", emp.id, emp.username, emp.password );
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

int handle_admin( int client_socket, struct User *admin ){
    
    while( 1 ){
        int opt;
        recv( client_socket, &opt, sizeof(opt), 0 );

        printf("%d\n", opt);
        switch ( opt ){
            case 1 :   // Add New Bank Employee
                addEmployee( client_socket );
                break;
            case 2 : { // Modify Customer/Employee Details
                int choice;
                recv(client_socket, &choice, sizeof(choice), 0);

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

                    // int employee_fd = open("./dataBaseFiles/employee/employee.txt", O_RDWR);
                    struct Employee employee;

                    // printf( "%d\n", sizeof(employee) * employee_id );
                    printf( "%d\n", employee_id );
                    // lseek(employee_fd, sizeof(employee) * employee_id, SEEK_SET);
                    // read(employee_fd, &employee, sizeof(employee));

                    // printf("%d, %s, %s\n", employee.id, employee.username, employee.password);

                    // char new_username[15];
                    // char new_password[15];
                    // recv(client_socket, new_username, sizeof(new_username), 0);
                    // recv(client_socket, new_password, sizeof(new_password), 0);

                    // strcpy(employee.username, new_username);
                    // strcpy(employee.password, new_password);

                    // lseek(employee_fd, sizeof(employee) * employee_id, SEEK_SET);
                    // write(employee_fd, &employee, sizeof(employee));

                    // close(employee_fd);

                    send(client_socket, "Employee details modified successfully", MAX_MESSAGE_SIZE, 0);
                } else {
                    send(client_socket, "Invalid choice", MAX_MESSAGE_SIZE, 0);
                }
                break;
            };
            break;
            case 3 : { // Manage User Roles

            }
            case 4 : { // Change Password

            }
            case 5 : { // Logout

            }
            case 6 : { // Exit

            }
            default :
                send(client_socket, "Invalid choice", MAX_MESSAGE_SIZE, 0);
                break;
        }
    }
    
    return 0;
}

int main(){
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_length = sizeof(client_addr);
    sem_t semaphore;

    // Create semaphore
    sem_init(&semaphore, 0, MAX_CLIENTS);

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket creation failed");
        exit(1);
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // Bind server socket to address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(1);
    }

    // Listen for incoming client connections
    if (listen(server_socket, 3) < 0) {
        perror("listen failed");
        exit(1);
    }
    else{
        printf("Server listening on port 8080...\n");
    }

    while( 1 ){
        int si = sizeof(client_addr);
        client_socket = accept( server_socket, (struct sockaddr *)&client_addr, &si );
        if (client_socket < 0) {
            perror("accept failed");
            continue;
        }

        pid_t pid = fork();
        if( pid == 0 ){
            // ************* CLIENT HANDLING *************
            struct User user = {"client1", "client123"};
            recv( client_socket, &user, sizeof(user), 0 );

            // user.username = "client";
            // user.password = "client123";

            // int users_file_fd = open( "users.txt", O_RDONLY | O_WRONLY );

            int isValid = handle_login( client_socket, &user );

            if( isValid ){
                printf("Admin operation started.....\n");
                // while( 1 ){
                    handle_admin( client_socket, &user );
                // }
            }
            
        }
        else{
            close( client_socket );
        }
    }

    return 0;
}