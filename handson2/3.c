/*
========================================================================================================
Name : 3
Author : Rakshit Pstel
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
                a. ITIMER_REAL
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

int main(){
	struct rlimit rl;

	if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        	perror("getrlimit");
        	return EXIT_FAILURE;
	}

	printf("Current limits:\n");
 	printf("  Soft limit: %ld\n", rl.rlim_cur);
 	printf("  Hard limit: %ld\n", rl.rlim_max);

	rl.rlim_cur = 2048;
	rl.rlim_max = 1048500;

	if (setrlimit(RLIMIT_NOFILE, &rl) == -1) {
        	perror("setrlimit");
        	return EXIT_FAILURE;
	}

    
	if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        	perror("getrlimit");
        	return EXIT_FAILURE;
	}

	printf("New limits:\n");
	printf("  Soft limit: %ld\n", rl.rlim_cur);
	printf("  Hard limit: %ld\n", rl.rlim_max);

    	return 0;
}

/*
========================================================================================================

Output:
./a.out 
Current limits:
  Soft limit: 1024
  Hard limit: 1048576
New limits:
  Soft limit: 2048
  Hard limit: 1048500

==============================================================================================
==========

*/

