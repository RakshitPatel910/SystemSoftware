#ifndef USER_STRUCT
#define USER_STRUCT

#include <stdbool.h>

struct User {
    // int acc_no;
    // float balance;
    // bool active;

    char username[50];
    char password[50];
};

struct Employee {
    int id;
    int role;
    char username[15];
    char password[15];
};

#endif