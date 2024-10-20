#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/ip.h>
#include<arpa/inet.h>

#define MAX_MESSAGE_SIZE 256

struct User{
    int id;
    int access_lvl;
    
    char username[50];
    char password[50];
};

struct Employee {
    int id;
    char username[15];
    char password[15];
};

int main(){
    int client_socket;
    int option;
    char message[256];
    struct sockaddr_in server_addr;

    client_socket = socket( AF_INET, SOCK_STREAM, 0 );
    if( client_socket < 0 ){
        perror("socket creation failed");
        exit(1);
    }

	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    int connection = connect( client_socket, (struct sockaddr *)&server_addr, sizeof( server_addr ) );
    if( connection < 0 ){
        perror("connection failed");
        exit(1);
    }

    while( 1 ){
        // ******************* LOGIN HERE *******************
        char init_read[1000];
        struct User user;
        user.id = -1;

        recv( client_socket, init_read, sizeof(init_read), 0 );
        printf( "%s", init_read );

        int login_type = -1;
        scanf( "%d", &login_type );
        user.access_lvl = login_type;

        printf("Enter Username: \n");
        scanf("%s", user.username);
        printf("Enter Password: \n");
        scanf("%s", user.password);

        send( client_socket, &user, sizeof(user), 0 );

        int access = 0;
        recv( client_socket, &access, sizeof(access), 0 );

        if( access < 1 ){
            printf("Login Unsuccessfull\n");
            return 0;
        }
        else{
            printf("Login successfull\n");
        }

        // while( 1 ){
        char read_buffer[1000], write_buffer[1000], buffer[1000];
        int read_bytes = 1, write_bytes;
        int flag = 1;
        while (read_bytes) {
            memset(read_buffer, 0, sizeof(read_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));

            read_bytes = recv(client_socket, read_buffer, sizeof(read_buffer), 0);
            printf( "%d\n", read_bytes );
            if (read_bytes == -1) {
                perror("Read from client socket\n");
                return 0;
            }
            if (read_bytes == 0) {
                printf("Didn't receive anything from server\n");
                return 0;
            }
            if ( strstr(read_buffer, "#*#logout#*#") != NULL ){
                printf("rby: %d, logout\n", read_bytes );
                break;
            }
            if (strchr(read_buffer, '$') != NULL) {
                strncpy(buffer, read_buffer, sizeof(read_buffer) - 2);
                printf("%s\n", buffer);
                break;
            }

            memset(write_buffer, 0, sizeof(write_buffer));
            printf("%s", read_buffer);
            if( flag ){
                getchar();
                flag = 0;
            }
            // printf("\n");
            // char buff[1000];
            scanf("%[^\n]%*c", write_buffer);

            // printf("e\n");
            // printf("%s\n", write_buffer);
            write_bytes = send(client_socket, write_buffer, sizeof(write_buffer), 0);
            // printf("%s\n", write_buffer);
            printf("%d\n", write_bytes);
            // printf("e\n");
            if (write_bytes == -1) {
                perror("Write to client socket\n");
                return 0;
            }
        }
        // }
    }

    return 0;
} 