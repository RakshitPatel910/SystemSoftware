/*
========================================================================================================
Name : 33_server
Author : Rakshit Patel
Description : Write a program to communicate between two machines using socket.
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

	int cli_size = sizeof(cli);
	int conn_fd = accept(sock, (struct sockaddr *)&cli, &cli_size);
	if (conn_fd == -1) {
		perror("Accept error");
		_exit(0);
	}

	char buf[100];
	printf("Write message from server to client: ");
	scanf("%[^\n]", buf);
	write(conn_fd, buf, sizeof(buf));

	read(conn_fd, buf, 100);
	printf("Data from client: %s\n", buf);

	close(sock);
}

/*
========================================================================================================

./a.out 
Socket created
Connection error: Connection refused


./b.out
Server socket created
Binding successful!
Listening for connections...
Write message from server to client: msg from server
Data from client: msg from client

./a.out
Socket created
Connection with server established
msg from client
Data from server: msg from server
Write message for server: Data sent to server

========================================================================================================
*/

