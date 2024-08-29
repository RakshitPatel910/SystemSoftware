#include<stdio.h>
#include<unistd.h>

int main(){
	char* a[] = { "ls", "-Rl", NULL };

	execv( "/bin/ls", a );

	return 0;
}
