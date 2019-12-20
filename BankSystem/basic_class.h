#pragma once
//account.h
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include<iostream>
#include "date.h"
#include <string>
#include <map>
using namespace std;


//-----------------累加器类的定义-------------------
class Accumulator {
public:
	Date lastDate;//上次存取钱的日期
	Date date;
	double value;//余额或欠款
	double sum;//用来计息的按日累加钱款总和

	
	Accumulator() :lastDate(date), value(0), sum(0.0) {}

	double getSum(Date date) const;
	void change(Date date, double value);
	void reset(Date date, double value);
};
class Account;
//---------------账本的定义---------------
class AccountRecord {
private:
	Date date;                 //日期
	const Account *account;    //账户
	double amount;     //金额
	double balance;    //余额
	std::string desc;   //说明
public:
	AccountRecord(const Date &date, const Account *account, double amount, double balance, const std::string&desc);
	void show() const;
};

typedef std::multimap<Date, AccountRecord> RecordMap;

//------------------账户类的定义---------------------
class Account {
private:

	string id;		//帐号
	double balance;		//余额
	static double total;
	static RecordMap recordmap;
protected:
	Account(const Date &date, const string &id);
	void record(const Date &date, double amount, const string &msg);
	void error(const string &msg) const;     //报错
public:
	
	Accumulator *acc = new Accumulator;	   //声明指针而非创建对象，从而调用重载构造函数而非默认构造函数
	const string getId() const { return id; }
	double getBalance() const { return balance; }

	virtual void deposit(const Date &date, double amount, const std::string &desc)=0;
	virtual void withdraw(const Date &date, double amount, const std::string &desc) = 0;
	virtual void settle(const Date &date) = 0;
	virtual void show() const { cout << id << "\tBalance: " << balance; };    	//显示账户信息

	static double getTotal() { return total; }//总额
	static void query(const Date& begin, const Date& end);
};

class SavingsAccount:public Account{ //储蓄账户类
private:
	double rate;
public:

	
	SavingsAccount(const Date &date, const string &id, double rate) :Account(date, id), rate(rate){};
	double getRate() const { return rate; }
	virtual void deposit(const Date &date, double amount, const std::string &desc);
	virtual void withdraw(const Date &date, double amount, const std::string &desc);
	virtual void settle(const Date &date);

};

class CreditAccount :public Account {

	double credit;
	double fee;
	double rate;

public:	
	CreditAccount(const Date &date, const string &id, double credit, double rate, double fee);
	double getDebt()const;
	double getCredit() const { return credit; }
	double getRate() const { return rate; }
	double getFee() const { return fee; }
	double getAvailableCredit() const;
	
	virtual void deposit(const Date &date, double amount, const std::string &desc);
	virtual void withdraw(const Date &date, double amount, const std::string &desc);
	virtual void settle(const Date &date);
	virtual void show()const;

};


#endif //__ACCOUNT_H__
