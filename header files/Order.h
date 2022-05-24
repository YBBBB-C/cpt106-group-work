#pragma once
#ifndef ORDER_H
#define ORDER_H
#include "Date.h"
#include"Control.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime> 
#pragma warning( disable : 4996 )
static double total = 0;
using namespace std;


class Order
{
private:
public:
	virtual void order() = 0;
};


string itos(int i) // change int type to string
{
	stringstream s;
	s << i;
	return s.str();
}

bool is_digit(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == '3'
		|| c == '4' || c == '5' || c == '6' || c == '7'
		|| c == '8' || c == '9') return true;
	return false;
}

int salesOFday(Date* date) {
	int sum = 0;
	int year, month, day;
	year = date->get_year();
	month = date->get_month();
	day = date->get_day();
	string str = itos(year) + '-' + itos(month) + '-' + itos(day) + ".txt";
	ifstream s;

	s.open(str);
	if (s.fail())
	{
		printf("no record\n");
		return sum;
	}

	string strs;
	while (cin >> strs)
	{	
		cout << strs << "\n";
		if ( strs.find(':')  != string::npos)
		{
			int number = 0;
			for (int i = 0; i < strs.length() ; ++i)
			{
				if(is_digit(strs[i])) number = number * 10 + strs[i] - '0';
			}
			sum += number;
		}
		
	}
	return sum;
}

void statistics(int a, int b)
{
	int i = a;
	int o = b;
	time_t timer;
	time(&timer);
	tm* t_tm = localtime(&timer);
	Date* d;
	d = new Date(t_tm->tm_year + 1900, t_tm->tm_mon + 1, t_tm->tm_mday);
	cout << "Today is" << t_tm->tm_year + 1900 << "/" << t_tm->tm_mon + 1 << "/" << t_tm->tm_mday << "/" << endl;
	cout << "Today, the ratio of eat-in consumption to take-out is:" << i << ":" << o << endl;
	cout << "Total sales of today is:" << salesOFday(d) << endl;
}



void search(Date* date)
{
	int year, month, day;
	year = date->get_year();
	month = date->get_month();
	day = date->get_day();
	string str = itos(year) + '-' + itos(month) + '-' + itos(day) + ".txt";
	ifstream s;
	
	s.open(str);// the day we want to search has no history order
	if (s.fail())
	{
		printf("no record\n");
		return;
	}
	string t[500];
	int l = 0;
	int h = 0;
	string j[500];
	int high[500] = { 0 };
	while (getline(s, t[l]))
	{
		cout << t[l] << endl;
		if (t[l].length() == 4)
		{
			high[h] = l;
			j[h++] = t[l];
		}
		l++;
	}
	s.close();
	cout << "Please input£º£¨1: delete£¬0: exit£©" << endl;
	int op;
	cin >> op;
	while (op != 0)
	{
		while (op != 1 && op != 0)
		{
			cout << "Wrong input, please try again" << endl;
			cout << "Please input£º£¨1: delete£¬0: exit)" << endl;
			cin >> op;
		}
		if (op == 1)
		{
			cout << "Please input the order(delete)" << endl;
			string op_;
			cin >> op_;
			int flag = -1;
			for (int i = 0; i < h; i++)
				if (op_ == j[i]) 
				{
					flag = i;
					break;
				}
			if (flag == -1)
			{
				cout << "The order does not exist" << endl;
				cout << "Please input£º£¨1: delete£¬0: exit) " << endl;
				cin >> op;
				continue;
			}
			else
			{
				if (high[flag + 1] != 0)
					for (int k = high[flag]; k < high[flag + 1]; k++)
						t[k] = "0";
				else
					for (int k = high[flag]; k < l; k++)
						t[k] = "0";
				ofstream s;
				s.open(str);
				for (int p = 0; p < l; p++)
				{
					if (t[p] != "0")
						s << t[p] << endl;
				}
				s.close();
			}
			cout << "Please input£º£¨1: delete£¬0: exit)" << endl;
			cin >> op;
		}
		if (op == 0) {
			break;
		}
	}
}
#endif
