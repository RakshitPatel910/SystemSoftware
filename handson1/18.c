/*
========================================================================================================

Name: 18
Author: Rakshit Patel
Description: Write a program to perform Record locking.
	a. Implement write lock
	b. Implement read lock
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

struct Record{
        int rnum;
        int val;
};

int readRec( int f, int recNum, struct Record* rec, struct flock* reclck ){
	lseek( f, recNum * sizeof(struct Record), SEEK_SET );
	
	reclck->l_type = F_RDLCK;
	reclck->l_whence = SEEK_CUR;
	reclck->l_len = sizeof(struct Record);

	int o = fcntl( f, F_SETLKW, reclck );
	
	printf("Acquired read lock!!!\n");
	
	int b =	read(f, rec, sizeof(struct Record) );

	printf("value in record %d is %d", rec->rnum, rec->val);

	getchar();
	getchar();
	printf("Releasing read lock.....\n");

	fcntl( f, F_SETLK, reclck );

	printf("Lock released!!!\n");

	return 0;
}

int writeRec( int f, int recNum, struct Record* rec, struct flock* reclck ){
        lseek( f, recNum * sizeof(struct Record), SEEK_SET );
	
	reclck->l_type = F_WRLCK;
        reclck->l_whence = SEEK_CUR;
	reclck->l_len = sizeof(struct Record);

	lseek( f, recNum * sizeof(struct Record), SEEK_SET );

        int o = fcntl( f, F_SETLKW, reclck );

	printf("Acquired write lock!!!\n");

	struct Record r2;
        int b = read(f, &r2, sizeof(struct Record) );

        printf("value in record %d is %d", r2.rnum, r2.val);

	lseek( f, recNum * sizeof(struct Record), SEEK_SET );

	r2.val++;
	write( f, &r2, sizeof(struct Record) ); 

	printf("value in record %d changed to %d", r2.rnum, r2.val);

        getchar();
	getchar();
        printf("Releasing write lock.....\n");

        fcntl( f, F_SETLK, reclck );

        printf("Lock released!!!\n");

        return 0;
}



int main( int argc, char** argv ){
        if( argc < 2 ) return 0;

        int f = open( argv[1], O_CREAT | O_RDWR, 0777 );

        struct flock reclck;
//        struct Record arrRec[3];
//        for( int i = 0; i < 3; i++ ){
//                struct Record r;
//                r.rnum = i;
//                r.val = 5;
//                arrRec[i] = r ;
//	}
//
//        int w = write(f, &arrRec, sizeof(arrRec) );

        int m;
	printf("For setting values enter 2\n");
	printf("For read enter 1\n");
	printf("For write enter 0\n");
	scanf("%d", &m);

	if( m == 2 ){
		struct Record arrRec[3];
        	for( int i = 0; i < 3; i++ ){
                	struct Record r;
                	r.rnum = i;
               		r.val = 0;
                	arrRec[i] = r ;
        	}

        	int w = write(f, &arrRec, sizeof(arrRec) );

		return 0;
	}

	int rnum;
	printf("\nChoose record from 0, 1, 2\n");
	scanf("%d", &rnum);

	struct Record r;

	if( m == 1 ){
		printf("Acquiring read lock.....\n");

		readRec( f, rnum, &r, &reclck );
	}
	else {
		printf("Acquiring write lock.....\n");

                writeRec( f, rnum, &r, &reclck );
	}

        return 0;
}

/*
========================================================================================================
Output:

./a.out records.txt 
For setting values enter 2
For read enter 1
For write enter 0
2

READ ON RECORD  0:
terminal 1:
./a.out records.txt
For setting values enter 2
For read enter 1
For write enter 0
1

Choose record from 0, 1, 2
0
Acquiring read lock.....
Acquired read lock!!!
value in record 0 is 0

terminal 2:
./a.out records.txt
For setting values enter 2
For read enter 1
For write enter 0
1

Choose record from 0, 1, 2
0
Acquiring read lock.....
Acquired read lock!!!
value in record 0 is 0

WRITE ON SAME AND DIFFERENT RECORDS:
terminal 1:
./a.out records.txt
For setting values enter 2
For read enter 1
For write enter 0
0

Choose record from 0, 1, 2
0
Acquiring write lock.....
Acquired write lock!!!
value in record 0 is 0value in record 0 changed to 1

terminal 2:
./a.out records.txt
For setting values enter 2
For read enter 1
For write enter 0
0

Choose record from 0, 1, 2
0
Acquiring write lock.....

terminal 3:
./a.out records.txt
For setting values enter 2
For read enter 1
For write enter 0
0

Choose record from 0, 1, 2
2
Acquiring write lock.....
Acquired write lock!!!
value in record 2 is 0value in record 2 changed to 1


========================================================================================================
*/

