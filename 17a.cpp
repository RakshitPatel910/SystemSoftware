/*
========================================================================================================

Name: 17
Author: Rakshit Patel
Description: Write a program to simulate online ticket reservation. Implement write lock Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
Date: 29th August, 2024

========================================================================================================
*/


#include<iostream>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string>
#include<cstring>

using namespace std;

int main( int argc, char** argv ){
	if( argc < 2 ) return 0;

	int f = open( argv[1], O_CREAT | O_RDWR, 0777 );

	struct flock wlock;
	wlock.l_type = F_WRLCK;
	wlock.l_whence = SEEK_SET;
	wlock.l_start = 0;
	wlock.l_len = 0;

	cout << "Acquiring write lock....." << endl;

        int o = fcntl( f, F_SETLKW, &wlock );

        cout << "Acquired write lock!!!" << endl;

       	cout << "Enter existing ticket number" << endl;

	string s;
	cin >> s;
        
	char buff[s.size() + 1];
    	strncpy(buff, s.c_str(), s.size());
    	buff[s.size()] = '\0';
	
	write( f, buff, sizeof(buff) );

	cout << "Releasing write lock....." << endl;

        fcntl( f, F_SETLK, &wlock );

        cout<< "Lock released!!!" << endl;

        close(f);

        return 0;
}
	
/*
========================================================================================================
Output:

./a.out tickets.txt 
Acquiring write lock.....
Acquired write lock!!!
Enter existing ticket number
6
Releasing write lock.....
Lock released!!!

========================================================================================================
*/

