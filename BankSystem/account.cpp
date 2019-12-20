//account.cpp
#include <iostream>
#include "basic_class.h"
#include"date.h"
#include <cmath>
#include <utility>
#include <map>
using namespace std::rel_ops;
using namespace std;


AccountRecord::AccountRecord(const Date &date, const Account *account, double amount, double balance, const std::string& desc)
	: date(date), account(account), amount(amount), balance(balance), desc(desc) { }

void AccountRecord::show() const {
	date.show();
	cout << "\t#" << account->getId() << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}


double Account::total = 0;
RecordMap Account::recordmap;
Account::Account(const Date & date, const string & id):id(id),balance(0) {
	date.show();
	cout << "\t#" << id << " created" << endl;
}

void Account::record(const Date &date, double amount, const string &desc) {
	
	amount = floor(amount * 100 + 0.5) / 100;	//保留小数点后两位
	balance += amount;
	total += amount;
	AccountRecord record(date, this, amount, balance, desc);
 	recordmap.insert(make_pair(date,record));
	record.show();
}

//查询指定账户
void Account::query(const Date& begin, const Date& end) {
	if (begin <= end) {
		RecordMap::iterator iter1 = recordmap.lower_bound(begin);
		RecordMap::iterator iter2 = recordmap.upper_bound(end);
		for (RecordMap::iterator iter = iter1; iter != iter2; ++iter)
			iter->second.show();
	}
}

void Account::error(const string &msg) const {
	cout << "Error(#" << id << "): " << msg << endl;
}



//SavingsAccount类相关成员函数的实现
void SavingsAccount::deposit(const Date &date, double amount, const string &desc) {
	record(date, amount, desc);
	acc->change(date, getBalance());
}

void SavingsAccount::withdraw(const Date &date, double amount, const string &desc) {
	if (amount > getBalance())
		error("not enough money");
	else
	{
		record(date, -amount, desc);
		acc->change(date, getBalance());
	}
}

void SavingsAccount::settle(const Date &date) {
	if (date.getMonth() == 1)
	{
		double interest = acc->getSum(date) * rate/ (date-Date(date.getYear() - 1, 1, 1));//计算年息
		if (interest != 0)
			record(date, interest, "interest");
		acc->reset(date, getBalance());
	}
}




CreditAccount::CreditAccount(const Date& date, const string& id, double credit, double rate, double fee)
	:Account(date, id), credit(credit), rate(rate), fee(fee) {}

double CreditAccount::getDebt() const
{
	double balance_t = getBalance();
	if (balance_t >= 0)
		return 0.0;
	else
		return balance_t;
}


double CreditAccount::getAvailableCredit() const
{
	if (getBalance() < 0)
		return credit + getBalance();
	else
		return credit;
}
	

void CreditAccount::deposit(const Date & date, double amount, const std::string & desc)
{
	record(date, amount, desc);
	acc->change(date, getDebt());
}

void CreditAccount::withdraw(const Date & date, double amount, const std::string & desc)
{
	if (amount - getBalance() > credit) {
		error("not enough credit");
	}
	else {
		record(date, -amount, desc);
		acc->change(date, getDebt());
	}
}

void CreditAccount::settle(const Date & date)
{
	//先计算利息
	
	double ins_t = acc->getSum(date)*rate;
	if (ins_t != 0)
		record(date, ins_t, " interest");
	//判断是否一月，减去年费
	if (date.getMonth() == 1)
	{
		record(date, -getFee(), "annual fee");
	}
	acc->reset(date, getDebt());

}


void CreditAccount::show() const{
	Account::show();
	cout <<  "\tAvailable credit:" << getAvailableCredit();
}
