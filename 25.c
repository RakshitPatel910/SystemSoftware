#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int p1 = fork();

	if( !p1 ){
		sleep(2);
		printf("1st child\n");
	}
	else{
		int p2 = fork();

		if( !p2 ){
			sleep(3);
			printf("2nd child\n");
		}
		else{
			int p3 = fork();

			if( !p3 ){
				sleep(4);
				printf("3rd child\n");
			}
			else{
				printf("waiting for 2nd child\n");
				waitpid( p2, NULL, 0 );
			}
		}
	}

	return 0;
}
