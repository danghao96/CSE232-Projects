/*
Hao Dang danghao@xserver
2016-04-10
proj09-bankaccount.cpp
*/

#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string;
#include <cctype>

#include "proj09-bankaccount.h"

BankAccount::BankAccount(string name, string password, double funds) {
	//This is a constructor for BankAccount.
	//This constructor will not allow password with non alnum characters
	//If the password contains non alnum character, it will throw an 
	//exception.
	//This constructor will not allow funds smaller than 0, if so, it
	//will reset the value of funds to 0.
	name_ = name;
	for (char c : password) {
		if (!isalnum(c)) {
			throw;
		}
	}
	password_ = password;
	if (funds > 0) {
		funds_ = funds;
	} else {
		funds_ = 0;
	}
}

ostream &operator<<(ostream &out, const BankAccount &ba) {
	//This is an override << operation for BankAccount.
	out << "Name:" << ba.name_ << ", " << "funds: " << ba.funds_;
	return out;
}
