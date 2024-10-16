#ifndef COMMONFUNC
#define COMMONFUNC

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <string.h>
#include <errno.h>

typedef enum {
    LOCK_SHARED = 1,
    LOCK_EXCLUSIVE = 2
} LockType;

int apply_file_lock(int fd, LockType lock_type, size_t struct_size, off_t offset) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));

    lock.l_type = (lock_type == LOCK_EXCLUSIVE) ? F_WRLCK : F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = struct_size;

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to apply lock");
        return -1;
    }

    return 0;
}

int release_file_lock(int fd, size_t struct_size, off_t offset) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));

    lock.l_type = F_UNLCK; 
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = struct_size;

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to release lock");
        return -1;
    }

    return 0;
}

#endif