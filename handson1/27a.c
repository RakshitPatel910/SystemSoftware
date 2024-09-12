/*
========================================================================================================

Name: 27a
Author: Rakshit Patel
Description: Write a program to execute ls -Rl by the following system calls
	a. execl
Date: 29th August, 2024

========================================================================================================
*/


#include<stdio.h>
#include<unistd.h>

int main() {
	execl( "/bin/ls", "ls", "-Rl", NULL );

	return 0;
}

/*
========================================================================================================
Output:

 ./a.out
.:
total 220
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1873 Aug 29 23:25 10.cpp
-rwxrwxr-x 1 rakshit-patel rakshit-patel    30 Aug 29 23:23 10_file.txt
-rw-rw-r-- 1 rakshit-patel rakshit-patel  2135 Aug 29 23:45 11.cpp
-rwxrwxr-x 1 rakshit-patel rakshit-patel   137 Aug 29 23:44 11_file.txt
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1709 Aug 29 23:57 12.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel     0 Aug 13 22:24 12_file.txt
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1281 Aug 30 00:02 13.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1749 Aug 30 00:09 14.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  4021 Aug 30 00:12 15.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1555 Aug 30 11:12 16a.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1463 Aug 30 11:12 16b.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1855 Aug 30 11:24 17a.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  2306 Aug 30 11:24 17b.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  4476 Aug 30 11:38 18.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1085 Aug 30 11:49 19.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1092 Aug 30 00:13 1a.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1204 Aug 29 22:31 1b.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1218 Aug 29 22:34 1c.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel   971 Aug 30 11:50 20.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1136 Aug 30 11:58 21.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1177 Aug 30 12:06 22.c
-rw-r--r-- 1 rakshit-patel rakshit-patel    50 Aug 30 12:05 22file.txt
-rw-rw-r-- 1 rakshit-patel rakshit-patel   836 Aug 30 12:09 23.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   943 Aug 30 12:11 24.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1150 Aug 30 12:18 25.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   851 Aug 30 12:32 26a.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1009 Aug 30 12:32 26b.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   105 Aug 29 17:46 27a.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   100 Aug 29 18:02 27b.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   139 Aug 29 18:01 27c.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   125 Aug 29 18:01 27d.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   121 Aug 29 18:00 27e.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   462 Aug 29 18:31 28.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  2036 Aug 29 19:00 29.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  2251 Aug 29 22:41 2.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel   577 Aug 29 19:51 30.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   967 Aug 30 00:13 3.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1226 Aug 29 22:53 4.cpp
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:52 4_file
-rw-rw-r-- 1 rakshit-patel rakshit-patel  2040 Aug 29 22:57 5.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1258 Aug 29 23:01 6.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1773 Aug 29 23:08 7.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1438 Aug 29 23:15 8.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1864 Aug 29 23:20 9.cpp
-rwxrwxr-x 1 rakshit-patel rakshit-patel 15960 Aug 30 12:37 a.out
-rwxrwxr-x 1 rakshit-patel rakshit-patel 16608 Aug 30 12:31 b.out
-r----x--t 1 rakshit-patel rakshit-patel     0 Aug 29 22:46 creat_file
--wxrw---t 1 rakshit-patel rakshit-patel     0 Aug 29 22:34 fifo_file
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:55 file_1
-rw-r--r-- 2 rakshit-patel rakshit-patel     0 Aug 30 12:31 file1.txt
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:55 file_2
-rw-r--r-- 1 rakshit-patel rakshit-patel    40 Aug 29 23:06 file2.txt
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:55 file_3
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:55 file_4
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:55 file_5
-rw-r--r-- 2 rakshit-patel rakshit-patel     0 Aug 30 12:31 hl_file1
-rw-rw-r-- 1 rakshit-patel rakshit-patel     0 Aug 29 22:28 hltemp
-rw-rw-r-- 1 rakshit-patel rakshit-patel    24 Aug 30 11:37 records.txt
lrwxrwxrwx 1 rakshit-patel rakshit-patel     9 Aug 29 22:23 sf_file1 -> file1.txt
-rw-r--r-- 1 rakshit-patel rakshit-patel     0 Aug 29 22:48 tempfile.txt
-rwxrwxr-x 1 rakshit-patel rakshit-patel     8 Aug 30 11:24 tickets.txt

========================================================================================================
*/

