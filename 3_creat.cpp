#include<iostream>
#include<fcntl.h>

int main(){
	int v = creat( "creat_file", 777 );

	std::cout << "File descriptor of 'creat_file' is : " << v << std::endl;

	return 0;
}
