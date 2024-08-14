#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string>
#include<cstring>

int main(){
	int f = open( "11_file.txt", O_CREAT | O_WRONLY, 0777 );

	char o[50] = "original text for file 11_file.txt ";

	write( f, o, strlen(o) );

	int d1 = dup( f );
	std::cout<<d1<<" is the new fd using dup!"<<std::endl;

	char b1[50] = "text appended using fd from dup! ";

	write( d1, b1, strlen(b1) );

	int d2 =  dup2( f, 87 );
        std::cout<<d2<<" is the new fd using dup2!"<<std::endl;
        
        char b2[50] = "text appended using fd from dup2! ";
        
        write( d2, b2, strlen(b2) );
	
	int fc1 = fcntl( f, F_DUPFD );
        std::cout<<fc1<<" is the new fd using fcntl!"<<std::endl;

        char b3[50] = "text appended using fd from fcntl! ";

        write( fc1, b3, strlen(b3) );

	char b4[200];
	while( true ){
		
		int s = read( f, b1, 1);
		if( s == 0 ) break;
	}

	write( 1, b4, strlen(b4) );

	return 0;

}
