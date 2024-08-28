#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct Record{
    int val;
};

int readRec( int f, int recNum, char* buff, struct flock* reclck ){
    reclck->l_type = F_RDLCK;
    reclck->l_whence = SEEK_SET;
    reclck->l_start = recNum * sizeof(struct Record);
    reclck->l_len = sizeof(struct Record);

    int o = fcntl( f, F_SETLKW, &reclck );

    lseek( f, recNum * sizeof(struct Record), SEEK_SET );
    read(f, buff, sizeof(struct Record) );

    getchar();

    reclck->l_type = F_UNLCK;
    fcntl( f, F_SETLK, reclck );

    return 0;
}

int writeRec( int f, int recNum, char* buff, struct flock* reclck ){
    reclck->l_type = F_WRLCK;
    reclck->l_whence = SEEK_SET;
    reclck->l_start = recNum * sizeof(struct Record);
    reclck->l_len = sizeof(struct Record);

    int o = fcntl( f, F_SETLKW, &reclck );

    lseek( f, recNum * sizeof(struct Record), SEEK_SET );

    struct Record r;
    r.val = 10;

    write(f, &r, sizeof(struct Record) );

    getchar();

    reclck->l_type = F_UNLCK;
    fcntl( f, F_SETLK, reclck );

    return 0;
}

int main( int argc, char** argv ){
    if( argc < 2 ) return 0;

    int f = open( argv[1], O_CREAT | O_RDWR, 0777 );

    struct Record arrRec[3];
    for( int i = 0; i < 3; i++ ){
        struct Record r;
        r.val = i;
        arrRec[i] = r ;
    }

    write(f, &arrRec, 3*sizeof(struct Record) );

    struct flock reclck;

    int m;
    printf("For read enter 1\n");
    printf("For write enter 0\n");
    scanf("%d", &m);

    int rnum;
    printf("\n Choose record from 1 to 3\n");
    scanf("%d", &rnum);

    if( rnum < 1 || rnum > 3 ){
        printf("Invalid record number. Please choose a number between 1 and 3.\n");
        return 1;
    }

    char buff[sizeof(struct Record)] = {0}; // Initialize buff

    if( m == 1 ){
        printf("Acquiring read lock.....\n");
        readRec( f, rnum - 1, buff, &reclck ); // Subtract 1 from rnum since array indices start at 0
        printf("Acquired read lock!!!\n");
        getchar();
        printf("Releasing read lock.....\n");
        printf("Lock released!!!\n");
    }
    else {
        printf("Acquiring write lock.....\n");
        writeRec( f, rnum - 1, buff, &reclck ); // Subtract 1 from rnum since array indices start at 0
        printf("Acquired write lock!!!\n");
        getchar();
        printf("Releasing write lock.....\n");
        printf("Lock released!!!\n");
    }

    close(f); // Close the file descriptor

    return 0;
}
