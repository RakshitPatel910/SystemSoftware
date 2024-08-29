#include<stdio.h>
#include<sched.h>

int main(){
	int fifomax = sched_get_priority_max( SCHED_FIFO );
	int fifomin = sched_get_priority_min( SCHED_FIFO );

	int rrmax = sched_get_priority_max( SCHED_RR );
	int rrmin = sched_get_priority_min( SCHED_RR );

	printf("Max priority for FIFO : %d\n", fifomax);
	printf("Min priority for FIFO : %d\n", fifomin);

	printf("Max priority for RR : %d\n", rrmax);
	printf("Min priority for RR : %d\n", rrmin);

	return 0;
}
