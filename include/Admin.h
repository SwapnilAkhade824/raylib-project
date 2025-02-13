#ifndef ADMIN_H
#define ADMIN_H

#pragma once
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
// #include "pages.h"
// #include "menus.h"
// #include "signup2.h"
#include "account.h"

long long generateUniqueId();
int addaccount();
int verifyaccount(long long int acc_num, const char *passwd);
void removeNewline(char *str);
void file();
void clrscr();

#define MAX_LINE_LENGTH 256
#define MAX_LENGTH 100

void removeNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

long long generateUniqueId() {
    srand(time(NULL));  

    long long newId;
    int exists;

    do {
        newId = (rand() % 9000000000LL) + 1000000000LL;  // Generate a 10-digit ID
        exists = 0;

        FILE *file = fopen("Signup.csv", "r");
        if (file == NULL) {
            perror("Error opening file");
            break;  // If file doesn't exist, consider ID unique
        }

        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file)) {
            long long fileId;
            sscanf(line, "%lld", &fileId);  // Read the ID from the line
            if (fileId == newId) {
                exists = 1;  // ID exists
                break;
            }
        }

        fclose(file);
        if (exists) {
            generateUniqueId();
        }
    } while (exists);

    return newId;
}


int addaccount(account acc)
{
    
	FILE *file;
	file=fopen("Signup.csv","a");

	if(file == NULL){
		printf("Error: Couldn't open the file");
		return 0;
	}

	fprintf(file,"%lld,%s,%s,%lld,%lld,%s\n",acc.acc_num,acc.name,acc.DOB,acc.aadhar_no,acc.mob_no,acc.passwd);

	fclose(file);
	return 1;

    FILE *bal;
    bal =fopen("balance.csv","a");
    fprintf(bal,"%lld,%lf",acc.acc_num,0.00);
    fclose(bal);
}




int verifyaccount(long long acc_num, const char *passwd) {
    FILE *file;
    file = fopen("Signup.csv", "r");  // Open the file in read mode

    if (file == NULL) {
        printf("Error: Couldn't open the file\n");
        return 0;
    }

    char line[256];
    // Skip the header line
    //fgets(line, sizeof(line), file);

    long long acc_no;
    char name[256],pass[256];
    int DOB,adhaar,phno;

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        // Corrected sscanf format
        if (sscanf(line, "%lld,%255[^,],%d,%d,%d,%255[^\n]", &acc_no, name, &DOB, &adhaar, &phno, pass) == 6) {
            if (acc_no == acc_num) {
                fclose(file);  // Ensure file is closed before returning
                if (strcmp(pass, passwd) == 0) {
                    return 1;  // Account and password match
                }
                return 0;  // Password does not match
            }
        }
    }
    return 0;

    fclose(file);
    // Account or password didn't match
}


void clear_screen() {
    system("clear");
}
#endif