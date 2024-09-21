/*
========================================================================================================
Name : 34a_server
Author : Rakshit Patel
Description : Write a program to create a concurrent server.
        a. use fork
Date: 20 Sept, 2024.
========================================================================================================
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>

void main() {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("Socket creation error");
		_exit(0);
	}
	printf("Server socket created\n");

	struct sockaddr_in srv, cli;
	srv.sin_addr.s_addr = htonl(INADDR_ANY);
	srv.sin_family = AF_INET;
	srv.sin_port = htons(8080);

	if (bind(sock, (struct sockaddr *)&srv, sizeof(srv)) == -1) {
		perror("Binding error");
		_exit(0);
	}
	printf("Binding successful!\n");

	if (listen(sock, 3) == -1) {
		perror("Listening error");
		_exit(0);
	}
	printf("Listening for connections...\n");

	while (1) {
		int cli_size = sizeof(cli);
		int conn_fd = accept(sock, (struct sockaddr *)&cli, &cli_size);
		if (conn_fd == -1) {
			perror("Accept error");
			_exit(0);
		} else {
			if (fork() == 0) {
				// In child
				char buf[100];
				printf("Write message from server to client: \n");
				scanf("%[^\n]", buf);
				write(conn_fd, buf, sizeof(buf));

				read(conn_fd, buf, 100);
				printf("Data from client: %s\n", buf);
				close(conn_fd); // Close child connection
				_exit(0); // Exit child process
			} else {
				// Parent
				close(conn_fd); // Close connection for parent
			}
		}
	}

	close(sock);
}

/*
========================================================================================================

./b.out 
Server socket created
Binding successful!
Listening for connections...
Write message from server to client: 
msg from server
Data from client: msg from client
Write message from server to client: 
msg from server
Data from client: msg from client2

./a.out
Socket created
Connection with server established
Data from server: msg from server
Write message for server:
msg from client
Data sent to server

./a.out
Socket created
Connection with server established
Data from server: msg from server
Write message for server:
msg from client2
Data sent to server

========================================================================================================
*/

