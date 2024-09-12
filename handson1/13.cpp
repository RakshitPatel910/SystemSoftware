/*
========================================================================================================

Name: 13
Author: Rakshit Patel
Description: Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in $man 2 select).
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<unistd.h>
#include<sys/select.h>
#include<cstring>

int main(){
	std::cout << "Start typing!!!\n" << std::endl;
	
	//char buf[100];
	fd_set f;
	FD_ZERO( &f );
	FD_SET( 0, &f );

	struct timeval t;
	t.tv_sec = 10;

	int b = select( 1, &f, NULL, NULL, &t );

	if( b == -1 ){
		std::cout << "Error reading!" << std::endl;
		return 0;
	}
	else if( b == 0 ){
		std::cout << "Nothing typed!" << std::endl;
		return 0;
	}
	else{
		std::cout << "Something read!" << std::endl;
		return 0;
	}
	
	return 0;
}	

/*
========================================================================================================
Output:

./a.out
Start typing!!!

some text
Something read!

========================================================================================================
*/

