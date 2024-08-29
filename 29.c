#include<stdio.h>
#include<unistd.h>
#include<sched.h>

int main(){
	int p = getpid();

	int schedpolicy = sched_getscheduler( p );

	switch( schedpolicy ){
		case SCHED_FIFO:
			printf("current policy : SCHED_FIFO\n");
			break;
		case SCHED_RR:
                        printf("current policy : SCHED_RR\n");
                        break;
		case SCHED_OTHER:
                        printf("current policy : SCHED_OTHER\n");
                        break;
		default:
			break;
	}

	int num;

	printf("Enter number for changing policy\n");
	printf("1 for FIFO\n");
	printf("2 for RR\n");
	printf("3 for OTHER\n");

	scanf("%d", &num);

	struct sched_param sp;

	switch( num ){
		case 1:
			sp.sched_priority = 99;
			if( sched_setscheduler(p, SCHED_FIFO, &sp) == -1 ){
				printf("setting error\n");
				perror(" ");
				return 0;
			}
			break;
		case 2:
                        sp.sched_priority = 99;
                        if( sched_setscheduler(p, SCHED_RR, &sp) == -1 ){
                                printf("setting error\n");
                                return 0;
                        }
                        break;
		case 3:
                        sp.sched_priority = 99;
                        if( sched_setscheduler(p, SCHED_OTHER, &sp) == -1 ){
                                printf("setting error\n");
                                return 0;
                        }
                        break;
		default:
			break;
	}

	int newp = getpid();

        int newschedpolicy = sched_getscheduler( newp );

        switch( newschedpolicy ){
                case SCHED_FIFO:
                        printf("current policy : SCHED_FIFO\n");
                        break;
                case SCHED_RR:
                        printf("current policy : SCHED_RR\n");
                        break;
                case SCHED_OTHER:
                        printf("current policy : SCHED_OTHER\n");
                        break;
                default:
                        break;
        } 

	return 0;
}
