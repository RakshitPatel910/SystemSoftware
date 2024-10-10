#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

struct Employee {
    int id;
    char username[15];
    char password[15];
};

int main(){
    struct Employee emp;

    int total_emp_fd = open( "./dataBaseFiles/employee/totalEmp.txt", O_RDWR );
    int emp_list_fd = open( "./dataBaseFiles/employee/employee.txt", O_RDWR );

    while( read( emp_list_fd, &emp, sizeof(emp) ) > 0 ){
        printf( "%d, %s, %s\n", emp.id, emp.username, emp.password );
    }

    // read( emp_list_fd, &emp, sizeof(emp) );


}