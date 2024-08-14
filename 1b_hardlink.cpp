#include<iostream>
#include<unistd.h>

using namespace std;

int main(){
	int v = link( "hl_temp", " hl_to_hl_temp" );
       	if( v == 0 ) cout << "Hard Link created successfully!!!" << endl;
	else cout << "Link creation failed!" << endl;

	return 0;	
}
