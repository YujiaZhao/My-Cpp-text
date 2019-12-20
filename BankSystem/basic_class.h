#pragma once
//account.h
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include<iostream>
#include "date.h"
#include <string>
#include <map>
using namespace std;


//-----------------�ۼ�����Ķ���-------------------
class Accumulator {
public:
	Date lastDate;//�ϴδ�ȡǮ������
	Date date;
	double value;//����Ƿ��
	double sum;//������Ϣ�İ����ۼ�Ǯ���ܺ�

	
	Accumulator() :lastDate(date), value(0), sum(0.0) {}

	double getSum(Date date) const;
	void change(Date date, double value);
	void reset(Date date, double value);
};
class Account;
//---------------�˱��Ķ���---------------
class AccountRecord {
private:
	Date date;                 //����
	const Account *account;    //�˻�
	double amount;     //���
	double balance;    //���
	std::string desc;   //˵��
public:
	AccountRecord(const Date &date, const Account *account, double amount, double balance, const std::string&desc);
	void show() const;
};

typedef std::multimap<Date, AccountRecord> RecordMap;

//------------------�˻���Ķ���---------------------
class Account {
private:

	string id;		//�ʺ�
	double balance;		//���
	static double total;
	static RecordMap recordmap;
protected:
	Account(const Date &date, const string &id);
	void record(const Date &date, double amount, const string &msg);
	void error(const string &msg) const;     //����
public:
	
	Accumulator *acc = new Accumulator;	   //����ָ����Ǵ������󣬴Ӷ��������ع��캯������Ĭ�Ϲ��캯��
	const string getId() const { return id; }
	double getBalance() const { return balance; }

	virtual void deposit(const Date &date, double amount, const std::string &desc)=0;
	virtual void withdraw(const Date &date, double amount, const std::string &desc) = 0;
	virtual void settle(const Date &date) = 0;
	virtual void show() const { cout << id << "\tBalance: " << balance; };    	//��ʾ�˻���Ϣ

	static double getTotal() { return total; }//�ܶ�
	static void query(const Date& begin, const Date& end);
};

class SavingsAccount:public Account{ //�����˻���
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
