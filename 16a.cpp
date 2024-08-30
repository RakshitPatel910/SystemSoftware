/*
========================================================================================================

Name: 16a
Author: Rakshit Patel
Description: Write a program to perform mandatory locking.
	a. Implement write lock
	b. Implement read lock
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<sys/file.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

using namespace std;

int main ( int argc, char** argv ){
	if(argc < 2) return 0;

        struct flock wlock;
        wlock.l_type = F_WRLCK;
        wlock.l_whence = SEEK_SET;
        wlock.l_start = 0;
        wlock.l_len = 0;

        int f = open( argv[1], O_WRONLY );

        cout << "Acquiring write lock....." << endl;

        int o = fcntl( f, F_SETLKW, &wlock );

        cout << "Acquired write lock!!!" << endl;

        getchar();

        cout << "Releasing write lock....." << endl;

        //rlock.l_type = F_UNLCK;
        fcntl( f, F_SETLK, &wlock );

        cout<< "Lock released!!!" << endl;

        close(f);

        return 0;
}	

/*
========================================================================================================
Output:

terminal 1:
./a.out file1.txt
Acquiring write lock.....
Acquired write lock!!!

terminal 2:
./a.out file1.txt
Acquiring write lock.....

terminal 3:
./b.out file1.txt
Acquiring read lock.....

========================================================================================================
*/
