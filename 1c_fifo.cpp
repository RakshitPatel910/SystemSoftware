#include<iostream>
#include<sys/stat.h>

int main() {
	int v { mknod( "fifo_file", 755, 0 ) };

	if( v == 0 ) std::cout << "FIFO created succesfully!!!" << std::endl;
       	else std::cout << "FIFO creation failed!" << std::endl;

	return 0;	
}
