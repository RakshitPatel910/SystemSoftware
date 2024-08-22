#include<iostream>

using namespace std;

extern char **environ;

int main(){
	for( char **e = environ; *e != NULL; e++){
		cout << *e << endl;
	}

	return 0;
}
