#pragma once
#ifndef RAW_H
#define RAW_H
#define MAXSIZE 10000
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


class Raw
{
private:
public:
	int rcount = 0;
	int rid[MAXSIZE] = { 0 };
	string rname[MAXSIZE];
	double rprice[MAXSIZE];
	void RAW();
	void rprint();
	void radd();
	void rmodify();
	void rsub();
	void rsearch();

};


void Raw::RAW()
{
	rcount = 0;
	ifstream raw;
	raw.open("raw.txt");
	while (raw >> rid[rcount] >>rname[rcount] >> rprice[rcount])
		rcount++;
	raw.close();
}
void Raw::rprint()
{
	cout << left << setw(10) << "dish ID " << left << setw(20) << "raw materials " << left << setw(30) << " rprice" << endl;
	for (int i = 0; i < rcount; i++)
	{
			cout << left << setw(15) << rid[i] << left << setw(20) << rname[i] << left << setw(10) << rprice[i] << endl;		
	}
}
void Raw::radd()
{
	rcount++;
	ofstream raw;
	raw.open("raw.txt", ios::app);
	cout << "raw meterial and price (format£ºfish+german-potato(some blank space here) raw_price	)" << endl;
	cin >> rname[rcount] >> rprice[rcount];
	raw << rcount << '\t' << rname[rcount] << '\t' << rprice[rcount];
	raw << endl;
	raw.close();
}
void Raw::rmodify()
{
	ofstream raw;
	raw.open("raw.txt");
	int num;
	cout << "Please input the dish ID (Whose materials you want to modify, or put 0 to exit)" << endl;
	cin >> num;
	while (num != 0)
	{
		if (num < 0 || num > rcount)
			cout << "The dish ID does not exist" << endl;
		else
		{
			cout << "Please input the dish name (modiyf name)" << endl;
			cout <<"(format£ºfish+german-potato(use '+' to link materials and '-' to replace blank space between words )" << endl; 
			string str;
			cin >> str;
			if (str != "0")
			{
				rname[num - 1] = "";
				rname[num - 1] = str;
			}
			cout << "Please input the raw price (modify price)" << endl;
			int p;
			cin >> p;
			if (p != 0)
				rprice[num - 1] = p;
		}
		cout << "Please input the dish ID" << endl;
		cin >> num;
	}
	for (int i = 0; i < rcount; i++)
	{
		
			raw << rid[i] << '\t' << rname[i] << '\t' << rprice[i] << endl;
	}
	raw.close();
}
void Raw::rsub()
{
	ofstream raw;
	raw.open("raw.txt");
	int num;
	cout << "Please input the raw dish ID (Delete material of dish)" << endl; //delete dishes
	cin >> num;
	while (num != 0)
	{
		if (num < 0 || num > rcount)
			cout << "the dish ID does not exist" << endl;
		else
		{
			rcount--;
			for (int i = num - 1; i < rcount; i++)
			{
				
				rname[i] = rname[i + 1];
				rprice[i] = rprice[i + 1];
			}
		}
		cout << "Please input the dish ID (Delete dish), or 0 to exit" << endl;
		cin >> num;
	}
	for (int i = 0; i < rcount; i++)
	{

			raw << rid[i] << '\t' << rname[i] << '\t' << '\t' << rprice[i] << endl;
	}
	raw.close();
}
void Raw::rsearch()
{
	ifstream raw;
	raw.open("raw.txt");
	int num;
	cout << "Please input the raw dish ID (Search)" << endl;
	cin >> num;
	while (num != 0)
	{
		if (num < 0 || num > rcount)
			cout << "The dish ID does not exist" << endl;
		else
		{
			cout << left << setw(10) << "dish ID " << left << setw(40) << "raw material name " << left << setw(10) << "r-price" << endl;
			cout << left << setw(10) << rid[num - 1] << left << setw(40) << rname[num - 1] << left << setw(10) << rprice[num - 1] << endl;
		}
		cout << "Please input the dish ID" << endl;
		cin >> num;
	}
	raw.close();
}

#endif
#pragma once
