#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

int main( int argc, char** argv ){
	if( argc < 4 ){
		printf("enter time in HH MM SS format!\n");
		return 0;
	}

	time_t st, en;
	struct tm* entime;

	time( &st );
	entime = localtime( &st );

	entime->tm_hour = atoi( argv[1] );
	entime->tm_min = atoi( argv[2] );
	entime->tm_sec = atoi( argv[3] );

	en = mktime( entime );

	int p = fork();

	if( p == 0 ){
		setsid();

		do{
			time( &st );
		} while( difftime( en, st ) > 0 );

		system("echo en time reached!!!\n");
	}
	else exit(0);

	return 0;
}
