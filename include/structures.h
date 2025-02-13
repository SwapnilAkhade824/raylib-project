#ifndef STRUCTURES_H
#define STRUCTURES_H

struct LoginCSV {
    long long accno;
    char username[10];
    char password[10];
};

struct DOB {
    int day,month,year;
};

struct SignUpCSV {
	long long accno;
    long long aadhaarno;
    char name[100];
    struct DOB dateofbirth;
    long long mobileno;
    char password[50];
};

struct BalanceCSV {
	long long accno;
	double balance;
};

struct TransactionCSV {
	long long accno;
	// date
	// time
	bool type;
	double amount;
}


#endif