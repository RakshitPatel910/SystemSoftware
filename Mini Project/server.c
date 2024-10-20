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

#include "./headers/admin.h"
#include "./headers/manager.h"
#include "./headers/employee.h"
#include "./headers/customer.h"
#include "./headers/commonFunc.h"
#include "./headers/const.h"

#include "./structures/users.h"

#define MAX_CLIENTS 10
#define MAX_MESSAGE_SIZE 256

int handle_login( int client_socket, struct User *user, struct sembuf *sem_op, int *sem_id ){
    // int users_file_fd = open( "users.txt", O_RDWR );
    // int total_user_fd = open( "totalClients", O_RDWR );
    // if ( users_file_fd == -1 || total_user_fd == -1 ) {
    //     perror("open");
    //     return 1;
    // } 
    
    int isValid = 0;
    if( user->access_lvl == 1 ){
        isValid = admin_login( client_socket, user, sem_op, sem_id );
    }
    else if ( user->access_lvl == 2 ){
        isValid = employee_login( client_socket, user, 1, sem_op, sem_id );
    }
    else if ( user->access_lvl == 3 ){
        isValid = employee_login( client_socket, user, 0, sem_op, sem_id );
    }
    else if ( user->access_lvl == 4 ){
        isValid = customer_login( client_socket, user, sem_op, sem_id );
    }
    else{

    }
    

    // struct User user_info;
    
    // int tu;
    // read( total_user_fd, &tu, sizeof(tu) );

    // lseek( users_file_fd, 0 , SEEK_SET );
    // // printf("%d\n",l);
    // printf( "%s\n", user->username );
    // printf( "%s\n", user->password );
    // while( read( users_file_fd, &user_info, sizeof(user_info) ) > 0 ){
        
    //     printf( "%s\n", user_info.username );
    //     printf( "%s\n", user_info.password );

    //     if( strcmp(user->username, user_info.username) == 0 && strcmp(user->password, user_info.password) == 0){
    //         isValid = 1;
    //         break;
    //     }
    // }

    // if ( isValid ) {
    //     printf("Login successful\n");
    //     send( client_socket, &isValid, sizeof(isValid), 0 );
    // } else {
    //     printf("Invalid username or password\n");
    //     send( client_socket, &isValid, sizeof(isValid), 0 );
    // }

    // close( users_file_fd );
    // close( total_user_fd );

    return isValid;
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
    if (listen(server_socket, 10) < 0) {
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
            close(server_socket);

            while( 1 ){

                struct User user;
                send( client_socket, INITIAL_PROMPT, strlen(INITIAL_PROMPT), 0 );
                recv( client_socket, &user, sizeof(user), 0 );


                struct sembuf sem_operation;
                int sem_id;

                int isValid = handle_login( client_socket, &user, &sem_operation, &sem_id );
                bool logout = false;

                if( isValid ){

                    printf("Client is connected to the server\n");

                    char read_buffer[1000], write_buffer[1000];
                    int read_bytes, write_bytes;
                    int choice;

                    switch ( isValid ) {
                        case 1:
                            logout = handle_admin(client_socket, &user);
                            break;
                        case 2:
                            logout = handle_manager(client_socket, &user);
                            break;
                        case 3:
                            logout = handle_employee(client_socket, &user, user.id);
                            break;
                        case 4:
                            logout =  handle_customer(client_socket, &user, user.id);
                            break;
                        default:
                            // exit_handler(client_socket);
                            break;
                    }
                // sleep(3);
                    if( logout == true ) {
                        unlock_login_sem( &sem_operation, sem_id );
                        printf("logout req\n");
                        // int iy = send( client_socket, "#*#logout#*#", strlen("#*#logout#*#"), 0 );
                        // printf("iy: %d\n", iy);
                        continue;
                    }
                    
                }
                else{

                }
                close( client_socket );
                _exit(0);


            }

            // struct User user;
            // send( client_socket, INITIAL_PROMPT, strlen(INITIAL_PROMPT), 0 );
            // recv( client_socket, &user, sizeof(user), 0 );

            // int isValid = handle_login( client_socket, &user );

            // if( isValid ){

            //     printf("Client is connected to the server\n");

            //     char read_buffer[1000], write_buffer[1000];
            //     int read_bytes, write_bytes;
            //     int choice;

            //     switch ( isValid ) {
            //         case 1:
            //             handle_admin(client_socket, &user);
            //             break;
            //         case 2:
            //             handle_manager(client_socket, &user);
            //             break;
            //         case 3:
            //             handle_employee(client_socket, &user, user.id);
            //             break;
            //         case 4:
            //             handle_customer(client_socket, &user, user.id);
            //             break;
            //         default:
            //             // exit_handler(client_socket);
            //             break;
            //     }
            // sleep(3);
                
            // }
            // else{

            // }
            // close( client_socket );
            // _exit(0);
            
        }
        else{
            close( client_socket );
            sleep(3);
        }
    }

    return 0;
}