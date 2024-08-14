#include<iostream>
#include<fcntl.h>

int main(){
	int v = open( "4_temp.txt", O_CREAT, O_RDWR );

	if( v == -1 ) std::cout << "File creation failed!" << std::endl;
	else std::cout << "File opened with RDWR with descriptor : " << v << std::endl;

	int v1 = open( "4_temp.txt", O_CREAT | O_EXCL, O_RDWR );

	if( v1 == -1 ) std::cout << "EXCL error!" << std::endl;
	else std::cout << "success!" << std::endl;

	return 0;
}
