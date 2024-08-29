#include<stdio.h>
#include<unistd.h>

int main(){
	int p = fork();

	if( !p ){
		printf("pid of Parent process before sleep : %d\n", getppid() );

		sleep(4);

		printf("pid of Parent process after sleep : %d\n", getppid() );
	}
	else{
		sleep(1);
	}

	return 0;
}
