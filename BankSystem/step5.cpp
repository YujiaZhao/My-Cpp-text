//step5.cpp
#pragma warning(disable:4996)
#include "basic_class.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <sstream>


using namespace std;


struct deleter {
	template <class T> void operator () (T* p) { delete p; }
};

int main() {
	Date date(2008, 11, 1);	//��ʼ����

	vector<Account *> accounts;	//�����˻����飬Ԫ�ظ���Ϊ0;

	char type;
	int index, day;
	double amount, credit, rate, fee;
	string id, desc;
	Account* account;
	Date date1, date2;
	char cmd;
	int flag = 0;

	string str;
	ifstream fout;
	fout.open("command.txt");
	while (fout.good())
	{
		getline(fout, str);
		istringstream is(str);
		is >> cmd;
		if (cmd != 'e') {
			switch (cmd) {
			case 'a':	//�����˻�
				is >> type >> id;
				if (type == 's') {
					is >> rate;
					account = new SavingsAccount(date, id, rate);
				}
				else {
					is >> credit >> rate >> fee;
					account = new CreditAccount(date, id, credit, rate, fee);
				}
				accounts.push_back(account);
				break;
			case 'd':	//�����ֽ�
				is >> index >> amount;
				desc = str;
				is >> str;
				accounts[index]->deposit(date, amount, desc);
				break;
			case 'w':	//ȡ���ֽ�
				is >> index >> amount;
				desc = str;
				is >> str;
				accounts[index]->withdraw(date, amount, desc);
				break;
			case 's':	//��ѯ���˻���Ϣ
				for (size_t i = 0; i < accounts.size(); i++) {
					cout << "[" << i << "] ";
					accounts[i]->show();
					cout << endl;
				}
				break;
			case 'c':	//�ı�����
				is >> day;
				if (day < date.getDay())
					cout << "You cannot specify a previous day";
				else if (day > date.getMaxDay())
					cout << "Invalid day";
				else
					date = Date(date.getYear(), date.getMonth(), day);
				break;
			case 'n':	//�����¸���
				if (date.getMonth() == 12)
					date = Date(date.getYear() + 1, 1, 1);
				else
					date = Date(date.getYear(), date.getMonth() + 1, 1);
				for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
					(*iter)->settle(date);
				break;
			case 'q':	//��ѯһ��ʱ���ڵ���Ŀ
				date1 = date1.read();
				date2 = date2.read();
				Account::query(date1, date2);

				break;
			}
		}
	}
	
	cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;
	fstream fin("command.txt", ios_base::app);
   
	do
	{
		
		//��ʾ���ں��ܽ��
		date.show();
		cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";
		cin >> cmd;
		if (cmd!= 'e' || cmd != 's' || cmd != 'q')
			fin << cmd;
		if (flag != 0)
		{
			fin << "\r\n";
		}
		
		flag = 1;
		switch (cmd) {
		case 'a':	//�����˻�
			cin >> type >> id;
			fin <<" "<< type<<" " << id<<" ";
			if (type == 's') {
				cin >> rate;
				fin << rate;
				account = new SavingsAccount(date, id, rate);
			}
			else {
				cin >> credit >> rate >> fee;
				fin <<" "<< credit << " " << rate << " " << fee;
				account = new CreditAccount(date, id, credit, rate, fee);
			}
			accounts.push_back(account);
			break;
		case 'd':	//�����ֽ�
			cin >> index >> amount;
			fin << ' '<<index <<' '<< amount<<' ';
			getline(cin, desc);
			fin << desc;
			accounts[index]->deposit(date, amount, desc);
			break;
		case 'w':	//ȡ���ֽ�
			cin >> index >> amount;
			fin <<' '<< index << ' ' << amount << ' ';
			getline(cin, desc);
			fin << desc;
			accounts[index]->withdraw(date, amount, desc);
			break;
		case 's':	//��ѯ���˻���Ϣ
			for (size_t i = 0; i < accounts.size(); i++) {
				cout << "[" << i << "] ";
				accounts[i]->show();
				cout << endl;
			}
			break;
		case 'c':	//�ı�����
			cin >> day;
			if (day < date.getDay())
				cout << "You cannot specify a previous day";
			else if (day > date.getMaxDay())
				cout << "Invalid day";
			else
				date = Date(date.getYear(), date.getMonth(), day);
			break;
		case 'n':	//�����¸���
			if (date.getMonth() == 12)
				date = Date(date.getYear() + 1, 1, 1);
			else
				date = Date(date.getYear(), date.getMonth() + 1, 1);
			for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
				(*iter)->settle(date);
			break;
		case 'q':	//��ѯһ��ʱ���ڵ���Ŀ
			date1 = date1.read();
			date2 = date2.read();
			Account::query(date1, date2);

			break;
		}
		
	} while (cmd != 'e');
	
	fin.close();
	

	for_each(accounts.begin(), accounts.end(), deleter());
	return 0;
}

