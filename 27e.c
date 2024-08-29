#include<stdio.h>
#include<unistd.h>

int main(){
	char* a[] = { "ls", "-Rl", NULL };

	execvp( "ls", a );

	return 0;
}
