/*
========================================================================================================
Name : 5
Author : Rakshit Patel
Description : Write a program to print the system limitation of
		a. maximum length of the arguments to the exec family of functions.
		b. maximum number of simultaneous process per user id.
		c. number of clock ticks (jiffy) per second.
		d. maximum number of open files
		e. size of a page
		f. total number of pages in the physical memory
		g. number of currently available pages in the physical memory.
Date: 16 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>


struct DS{
	int macro;
	const char* s;
};

int main(){
	struct DS m[] = {
		{_SC_ARG_MAX, "Maximum length of the arguments to the exec family of functions"},
		{_SC_CHILD_MAX, "Maximum number of simultaneous process per user id"},
		{_SC_CLK_TCK, "Number of clock ticks (jiffy) per second."},
		{_SC_OPEN_MAX, "Maximum number of open files"},
		{_SC_PAGESIZE, "Size of a page"},
		{_SC_PHYS_PAGES, "Total number of pages in the physical memory"},
		{_SC_AVPHYS_PAGES, "Number of currently available pages in the physical memory"},
	};

	int n = sizeof(m)/sizeof(m[0]);

	for(int i = 0; i<n; i++){
		long val = sysconf(m[i].macro);
		printf("%s: %ld\n", m[i].s, val);
	}

}

/*
========================================================================================================
Output:

./a.out
Maximum length of the arguments to the exec family of functions: 2097152
Maximum number of simultaneous process per user id: 62988
Number of clock ticks (jiffy) per second.: 100
Maximum number of open files: 1024
Size of a page: 4096
Total number of pages in the physical memory: 4049966
Number of currently available pages in the physical memory: 2761750

========================================================================================================
*/
