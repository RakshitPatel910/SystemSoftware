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
