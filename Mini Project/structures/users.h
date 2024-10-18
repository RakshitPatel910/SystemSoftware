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
    int loanID;

    char username[15];
    char password[15];
    int transaction[15];
    int tp;
};

struct Employee {
    int id;
    int role;

    char username[15];
    char password[15];

    int totalLoanAssigned;
    int loanAssigned[15];
};

#endif