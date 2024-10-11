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
    char username[50];
    char password[50];
};

struct Employee {
    int id;
    char username[15];
    char password[15];
};

int addEmployee( int client_socket ){
    struct Employee emp;
    
    emp.id = 0;
    printf("Enter new employee Username: ");
    scanf("%s", emp.username);
    printf("Enter new employee Password: ");
    scanf("%s", emp.password);

    printf( "%d, %s, %s\n", emp.id, emp.username, emp.password );
    send( client_socket, &emp, sizeof(emp), 0 );
    
    return 0;
}

int handle_admin( int client_socket, struct User *admin ){
    // int opt;
    // recv( client_socket, &opt, sizeof(opt), 0 );
    // printf("Enter option number: ");
    // scanf("%d", &opt );

    // send( client_socket, &opt, sizeof(opt), 0 );

    while( 1 ){
        int opt = 0;

        printf("Enter option number: ");
        scanf("%d", &opt );

        send( client_socket, &opt, sizeof(opt), 0 );

        if (opt == 1) { // Add New Bank Employee
            addEmployee(client_socket);
        } 
        else if (opt == 2) { // Modify Customer/Employee Details
            int choice;
            printf("Enter your choice:\n1. Modify Customer Details\n2. Modify Employee Details\n");
            scanf("%d", &choice);
            send(client_socket, &choice, sizeof(choice), 0);

            if (choice == 1) { // Modify Customer Details
                // Code for modifying customer details goes here
                /*
                int customer_id;
                printf("Enter customer ID: ");
                scanf("%d", &customer_id);
                send(client_socket, &customer_id, sizeof(customer_id), 0);

                char new_username[50];
                char new_password[50];
                float new_balance;
                printf("Enter new username: ");
                scanf("%s", new_username);
                printf("Enter new password: ");
                scanf("%s", new_password);
                printf("Enter new balance: ");
                scanf("%f", &new_balance);

                send(client_socket, new_username, sizeof(new_username), 0);
                send(client_socket, new_password, sizeof(new_password), 0);
                send(client_socket, &new_balance, sizeof(new_balance), 0);

                char message[MAX_MESSAGE_SIZE];
                recv(client_socket, message, MAX_MESSAGE_SIZE, 0);
                printf("%s\n", message);
                */
            } else if (choice == 2) { // Modify Employee Details
                int employee_id;
                printf("Enter employee ID: ");
                scanf("%d", &employee_id);
                send(client_socket, &employee_id, sizeof(employee_id), 0);

                struct Employee emp;
                emp.id = employee_id;
                printf("Enter new username: ");
                scanf("%s", emp.username);
                printf("Enter new password: ");
                scanf("%s", emp.password);
                send(client_socket, &emp, sizeof(emp), 0);

                char message[MAX_MESSAGE_SIZE];
                recv(client_socket, message, MAX_MESSAGE_SIZE, 0);
                printf("%s\n", message);
            }
            } else if (opt == 3) { // Manage User Roles
                // Code for managing user roles goes here
            } else if (opt == 4) { // Change Password
                // Code for changing password goes here
            } else if (opt == 5) { // Logout
                // Code for logout goes here
            } else if (opt == 6) { // Exit
                // Code for exit goes here
            } else {
                send(client_socket, "Invalid choice", 256, 0);
            }


    }

    
    
    return 0;
}

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


    // ******************* LOGIN HERE *******************
    struct User user;
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

    while (read_bytes) {
        memset(read_buffer, 0, sizeof(read_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));

        read_bytes = recv(client_socket, read_buffer, sizeof(read_buffer), 0);
        if (read_bytes == -1) {
            perror("Read from client socket\n");
            return 0;
        }
        if (read_bytes == 0) {
            printf("Didn't receive anything from server\n");
            return 0;
        }
        if (strchr(read_buffer, '$') != NULL) {
            strncpy(buffer, read_buffer, sizeof(read_buffer) - 2);
            printf("%s\n", buffer);
            break;
        }

        memset(write_buffer, 0, sizeof(write_buffer));
        printf("%s\n", read_buffer);
        // getchar();
        
        scanf("%[^\n]%*c", write_buffer);

        printf("e\n");
        printf("%s\n", write_buffer);
        write_bytes = send(client_socket, write_buffer, sizeof(write_buffer), 0);
        printf("e\n");
        if (write_bytes == -1) {
            perror("Write to client socket\n");
            return 0;
        }
    }
    // }

    return 0;
} 