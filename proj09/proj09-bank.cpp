/*
Hao Dang danghao@xserver
2016-04-10
proj09-bank.cpp
*/

#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string;
#include <map>
using std::map;
#include <random>
using std::default_random_engine; using std::uniform_int_distribution;
#include <limits>
using std::numeric_limits;

#include "proj09-bank.h"

Bank::Bank(string name, int seed) {
	//This is a constructor for Bank.
	name_ = name;
	accounts_.clear();
	
	//This will generate a bank_id_ using the given seed.
	rand_eng_ = default_random_engine (seed);
	uniform_int_distribution<long> dist(10000, 99999);
	bank_id_ = dist(rand_eng_);
}

long Bank::bank_id() {
	//This function returns bank_id_;
	return bank_id_;
}

string Bank::bank_name() {
	//This function returns name_;
	return name_;
}

long Bank::create_account(string account_name, 
string password, double funds) {
	//This function will create an account for the Bank, with the given
	//account_name, password, and initial funds.
	
	//This will generate an account_id for the account.
	uniform_int_distribution<long> dist(10000, 99999);
	long account_id = dist(rand_eng_);
	
	BankAccount ba(account_name, password, funds);	//create BankAccount.
	accounts_[account_id] = ba;	//put the new BankAccount in the map.
	return account_id;
}

double Bank::balance(long account_id, string password) {
	//This function will return the account balance. This function
	//requires account_id and password for that account.
	
	double result = numeric_limits<double>::min();
	if (accounts_.find(account_id) != accounts_.end() 
	&& password == accounts_[account_id].password_) {
		//if statement test if the account exists and password correct.
		result = accounts_[account_id].funds_;
	}
	return result;
}

bool Bank::transfer(long from_id, string from_password, 
long to_id, string to_password, double amount) {
	//This function will provide a way to transfer funds between accounts
	//It will return a bool value indicate if the transfer succeed.
	//This function requires from_id, from_password, to_id, to_password,
	// and amount.
	bool result = false;
	if ((accounts_.find(from_id) != accounts_.end() 
		 && accounts_.find(to_id) != accounts_.end())	//test existence
	&& (from_password == accounts_[from_id].password_ 
		&& to_password == accounts_[to_id].password_)	//test password
	&& (amount <= accounts_[from_id].funds_ && amount >= 0)) {
		//test amount.
		
		//transfer funds.
		accounts_[from_id].funds_ -= amount;
		accounts_[to_id].funds_ += amount;
		
		result = true;
		
	}
	return result;
}

void Bank::print_account(long id, string password, ostream& out) {
	//This function will print the account id, name, and funds in it.
	//If requires the account id and password for that account, and an
	//out stream for output.
	if (accounts_.find(id) == accounts_.end()) {	//test existence
		out << "No Such Account" << endl;
		return;
	}
	if (password != accounts_[id].password_) {		//test password
		out << "Bad PASSWORD" << endl;
		return;
	}
	out << "ID:" << id << ", " << accounts_[id] << endl;	//output
}
