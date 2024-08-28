#include<iostream>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string>
#include<cstring>
#include<stdlib.h>
#include<cmath>

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
	
	char c;
	int len;
	while( read( f, &c,1 )){
		if( c == '\0' ) break;
		len++;
	}

	char buff[len + 1];
	lseek(f, 0, SEEK_SET);
	len = 0;
	while( read( f, buff + len, 1) ){
		if( buff[len] == '\0' ) break;
		len++;
	}

	int tn;
	sscanf( buff, "%d", &tn);
	cout << tn << " " << ++tn << endl;;

	char buff1[ (int)((ceil(log10(tn))+1)*sizeof(char)) ];
	sprintf( buff1, "%d", tn);
	lseek( f, 0, SEEK_SET );
	write( f, buff1, sizeof(buff1) );

	cout << "Releasing write lock....." << endl;

        //rlock.l_type = F_UNLCK;
        fcntl( f, F_SETLK, &wlock );

        cout<< "Lock released!!!" << endl;

        close(f);

        return 0;
}

