#include<stdio.h>
#include<unistd.h>

int main(){
	int p = fork();

	if( !p ){
		printf( "child process with pid : %d\n", getpid() );
	}
	else{
		printf( "Press enter\n " );
		getchar();
	}

	return 0;
}
