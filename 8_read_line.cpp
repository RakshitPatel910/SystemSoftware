#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main(){
	int f = open( "file2.txt", O_RDONLY );

	if( f == -1 ){
	       	std::cout<< "Error opening file!" << std::endl;
		return 0;
	}

	char b[100];
	int c = 0;
	while( true ){

		int w = read( f, b + c, 1 );

		if( w == -1 ){
		       	std::cout << "Error reading!" << std::endl;
			return 0;
		}

		if( b[c++] == '\n' ){
		       	write( 1, b, c );
			c = 0;
			getchar();
		}

		if( w == 0 ) break;
	}
	
	close(f);

	return 0;

}	
