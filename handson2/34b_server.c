/*
========================================================================================================
Name : 34b_server
Author : Rakshit Patel
Description : Write a program to create a concurrent server.
        b. use pthread_create
Date: 20 Sept, 2024.
========================================================================================================
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void communicate(int *conn_fd) {
	char buf[100];
	write(*conn_fd, "Hello from server\n", 19);
	read(*conn_fd, buf, 100);
	printf("Data from client: %s\n", buf);
	close(*conn_fd);
}

void main() {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("Socket creation error");
		return;
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

	if (listen(sock, 2) == -1) {
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
			pthread_t threadID;
			if (pthread_create(&threadID, NULL, (void *)communicate, &conn_fd))
				perror("Thread creation error");
		}
	}
	close(sock);
}

/*
========================================================================================================

./a.out
Socket created
Connection with server established
Data from server: Hello from server

Write message for server:
msg from client1
Data sent to server


./a.out
Socket created
Connection with server established
Data from server: Hello from server

Write message for server:
msg from client2
Data sent to server


./b.out
Server socket created
Binding successful!
Listening for connections...
Data from client: msg from client1
Data from client: mag from client2
^C

========================================================================================================
*/

