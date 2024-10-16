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

struct Customer {
    int acc_no;
    float balance;
    bool active;
    int loan_status;

    char username[15];
    char password[15];
    int transaction[ 15 ];
};

struct Employee {
    int id;
    int role;
    char username[15];
    char password[15];
    int loanAssigned[15];
};

#endif