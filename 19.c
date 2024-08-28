#include<stdio.h>
#include<time.h>
#include<unistd.h>

int main(){
	struct timespec st, en;
	long double s, ns;

	clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &st );

	getpid();

	clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &en );

	s = ( en.tv_sec - st.tv_sec );
	ns = ( en.tv_nsec - st.tv_nsec );

	printf( "time taken by getpid() function : %Lf sec and %Lf nanosec\n", s, ns );

	return 0;
}
