#include<iostream>
#include<unistd.h>

using namespace std;

int main(){
	int v { symlink( "sf_temp", "sf_to_sf_temp" ) };

	if( v == 0 ) cout << "Soft Link created!!!" << endl;
	else cout << "Link Creation failed!" << endl;

	return 0;	
}
