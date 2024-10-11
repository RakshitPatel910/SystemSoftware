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
#include "./headers/const.h"

#define MAX_CLIENTS 10
#define MAX_MESSAGE_SIZE 256

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

            struct User user = {"client1", "client123"};
            recv( client_socket, &user, sizeof(user), 0 );

            // user.username = "client";
            // user.password = "client123";

            // int users_file_fd = open( "users.txt", O_RDONLY | O_WRONLY );

            int isValid = handle_login( client_socket, &user );

            if( isValid ){

                printf("Client is connected to the server\n");

                char read_buffer[1000], write_buffer[1000];
                int read_bytes, write_bytes;
                int choice;

                write_bytes = send(client_socket, INITIAL_PROMPT, strlen(INITIAL_PROMPT), 0);
                // write_bytes = send(client_socket, "INITIAL_PROMPT", strlen("INITIAL_PROMPT"), 0);
                if (write_bytes == -1) {
                    perror("Sending initial prompt\n");
                    return 0;
                }
                memset(read_buffer, 0, sizeof(read_buffer));

                printf("1st\n");
                read_bytes = recv(client_socket, &read_buffer, sizeof(read_buffer)-1, 0);
                printf( "%d, %d\n", read_bytes, choice );
                if (read_bytes == -1) {
                    perror("Reading choice\n");
                    return 0;
                }
                if (read_bytes == 0) {
                    printf("No data from client\n");
                }

                printf("2ndt\n");
                choice = atoi(read_buffer);
                printf("choice %d\n", choice);

                switch (choice) {
                    case 1:
                        handle_admin(client_socket, &user);
                        break;
                    case 2:
                        // manager_handler(client_socket);
                        break;
                    case 3:
                        // employee_handler(client_socket);
                        break;
                    case 4:
                        // customer_handler(client_socket);
                        break;
                    default:
                        // exit_handler(client_socket);
                        break;
                }
            sleep(3);
                
            }
            else{

            }
            close( client_socket );
            _exit(0);
            
        }
        else{
            close( client_socket );
            sleep(3);
        }
    }

    return 0;
}