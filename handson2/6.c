/*
========================================================================================================
Name : 6
Author : Rakshit Patel
Description : Write a simple program to create three threads.
Date: 16 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* t_func(void* i ){
	printf("Thread %d in execution!\n", *((int*)i));
		
	pthread_exit(NULL);
}

int main(){
	pthread_t t[3];
	int tid[3];
	int i;
	for( i = 0; i < 3; i++){
		tid[i] = i+1;

		if( pthread_create(&t[i], NULL, t_func, (void*)&tid[i]) ){
			printf("error\n");
		}
	}

	for(int i = 0; i < 3; i++){
		pthread_join( t[i], NULL );
	}

	printf("All  threads execution completed!\n");

	return 0;
}

/*
========================================================================================================
Output:

./a.out
Thread 1 in execution!
Thread 2 in execution!
Thread 3 in execution!
All  threads execution completed!

========================================================================================================
*/
