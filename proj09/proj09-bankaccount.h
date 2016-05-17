/*
Hao Dang danghao@xserver
2016-04-10
proj09-bankaccount.cpp

This head file provides a difinition for BankAccount class
*/

#ifndef BANKACCOUNT
#define BANKACCOUNT

#include <iostream>
using std::ostream;
#include <string>
using std::string;

class BankAccount{
  friend class Bank;
  private:
	string name_ = "";
	string password_ = "";
	double funds_ = 0;
	
  public:
	BankAccount()=default;
	BankAccount(string name, string password, double funds = 0);
	friend ostream &operator<<(ostream&, const BankAccount&);
};

#endif

