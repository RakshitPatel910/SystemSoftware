#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main( int argc, char** argv ){
	if( argc < 2 ){
		printf("Enter file name\n");
		return 0;
	}

	int f = open( argv[1], O_CREAT | O_RDWR, 0777 );

	fork();

	int pri = getpid();

	char buff[16] = "File Updated!!!\n";

	write( f, buff, 16 );

	return 0;
}	
