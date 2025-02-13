#include <stdio.h>
#include "../include/signup2.h"
#include "../include/Admin.h"
#include "../include/account.h"
int main()
{
	account acc = signupgui();
	addaccount(acc);
	return 0;
}