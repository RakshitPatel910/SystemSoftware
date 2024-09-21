/*
========================================================================================================
Name : 34a_client
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
	printf("Socket created\n");

	struct sockaddr_in addr;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);

	int conn = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
	if (conn == -1) {
		perror("Connection error");
		_exit(0);
	}
	printf("Connection with server established\n");

	char buf[100];
	read(sock, buf, 100);
	printf("Data from server: %s\n", buf);

	printf("Write message for server: \n");
	scanf("%[^\n]", buf);

	write(sock, buf, sizeof(buf));
	printf("Data sent to server\n");

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

