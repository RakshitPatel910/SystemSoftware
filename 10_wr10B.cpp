#include<iostream>
#include<unistd.h>
#include<fcntl.h>

int main(){
	int f = open( "10_file.txt", O_CREAT | O_RDWR, 0777 );

	if( f == -1 ){
		std::cout << "File related error!" << std::endl;
		return 0;
	}

	char b[11] = "0123456789";

	int w = write( f, b, 10 );
	if( w == -1 ) {
		std::cout << "Writing error!" << std::endl;
		return 0;
	}

	int o = lseek( f, 10, SEEK_CUR );
	if( o == -1 ){
		std::cout << "lseek error!" << std::endl;
		return 0;
	}
	else std::cout<< "O/p of lseek: " << o << std::endl; 

	w = write( f, b, 10 );
	if( w == -1 ) {
		std::cout << "Writing2 error!" << std::endl;
		return 0;
	}

	lseek( f, 0, SEEK_SET );

	char buff[30];

	w = read( f, buff, 30);

	write(1, buff, 30);

	return 0;

}
