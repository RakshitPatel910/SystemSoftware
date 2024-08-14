#include<iostream>
#include<sys/stat.h>

int main(){
	struct stat s;
	int i = stat( "file2.txt", &s );

	if( i == -1 ){
	       	std::cout << "Error retrieving info!" << std::endl;
		return 0;
	}

	std::cout << "inode: " << s.st_ino << std::endl;
	std::cout << "no. of hard link: " << s.st_nlink << std::endl;
	std::cout << "uid: " << s.st_uid << std::endl;
	std::cout << "gid: " << s.st_gid << std::endl;
	std::cout << "size: " << s.st_size << std::endl;
	std::cout << "block size: " << s.st_blksize << std::endl;
	std::cout << "no. of blocks: " << s.st_blocks << std::endl;
	std::cout << "time of last access: " << s.st_atime << std::endl;
	std::cout << "time of last modification: " << s.st_mtime << std::endl;
	std::cout << "time of last change: " << s.st_ctime << std::endl;

	return 0;
}
	
