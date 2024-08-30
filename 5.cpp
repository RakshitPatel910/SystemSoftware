/*
========================================================================================================

Name: 5
Author: Rakshit Patel
Description: Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
Date: 29th August, 2024

========================================================================================================
*/


#include<iostream>
#include<fcntl.h>
#include<string>

int main(){
	int count { 1 };

	while( true ) {
		if( count <= 5 ) {
			std::string s { "file_" };
			s += std::to_string( count );

			int d = creat( s.c_str(), O_RDWR );

			if( d == -1 ) std::cout << s << " creation failed!" << std::endl;
			else std::cout << s << " created!!!" << std::endl;

			count++;
		}
	}

	return 0;
}

/*
========================================================================================================
Output:

./a.out
file_1 created!!!
file_2 created!!!
file_3 created!!!
file_4 created!!!
file_5 created!!!

ls -la  /proc/4910/fd
total 0
dr-x------ 2 rakshit-patel rakshit-patel  8 Aug 29 22:56 .
dr-xr-xr-x 9 rakshit-patel rakshit-patel  0 Aug 29 22:55 ..
lrwx------ 1 rakshit-patel rakshit-patel 64 Aug 29 22:57 0 -> /dev/pts/4
lrwx------ 1 rakshit-patel rakshit-patel 64 Aug 29 22:57 1 -> /dev/pts/4
lrwx------ 1 rakshit-patel rakshit-patel 64 Aug 29 22:57 2 -> /dev/pts/4
l-wx------ 1 rakshit-patel rakshit-patel 64 Aug 29 22:57 3 -> /home/rakshit-patel/SystemSoftware/file_1
l-wx------ 1 rakshit-patel rakshit-patel 64 Aug 29 22:57 4 -> /home/rakshit-patel/SystemSoftware/file_2
l-wx------ 1 rakshit-patel rakshit-patel 64 Aug 29 22:57 5 -> /home/rakshit-patel/SystemSoftware/file_3
l-wx------ 1 rakshit-patel rakshit-patel 64 Aug 29 22:57 6 -> /home/rakshit-patel/SystemSoftware/file_4
l-wx------ 1 rakshit-patel rakshit-patel 64 Aug 29 22:57 7 -> /home/rakshit-patel/SystemSoftware/file_5

========================================================================================================
*/


