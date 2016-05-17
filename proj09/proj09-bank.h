/*
Hao Dang danghao@xserver
2016-04-10
proj09-bank.h

This head file provides a difinition for Bank class
*/

#ifndef BANK
#define BANK

#include <string>
using std::string;
#include <map>
using std::map;
#include <random>
using std::default_random_engine;

#include "proj09-bankaccount.h"


class Bank{
  private:
	string name_;
	long bank_id_;
	map<long, BankAccount> accounts_;
	default_random_engine rand_eng_;
  public:
	Bank(string name, int seed = 1234);
	long bank_id();
	string bank_name();
	long create_account(string account_name, string password, double funds = 0);
	double balance(long, string);
	bool transfer(long, string, long, string, double);
	void print_account(long, string, ostream&);
};

#endif
