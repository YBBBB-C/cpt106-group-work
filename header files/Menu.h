#pragma once
#ifndef MENU_H
#define MENU_H
#define MAXSIZE 10000
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Raw.h"
using namespace std;//
double discount = 10;


class Menu
{
private:
public:
	int count = 0;
	int id[MAXSIZE] = { 0 };
	string name[MAXSIZE];
	double price[MAXSIZE];
	void MENU();
	void print();
	void add();
	void modify();
	void sub();
	void search();
	//void setdiscount(double b);

};


void Menu::MENU()
{
	count = 0;
	ifstream menu;
	menu.open("menu.txt");
    while (menu >> id[count] >> name[count] >> price[count])
	count++;
    menu.close();
}
void Menu::print()
{
	cout << "count is " << count << endl;
	cout  << left << setw(10) << "dish ID " << left << setw(40) << "dish name " << left << setw(10) << "price" << endl;
	for (int i = 0; i < count; i++)
	{
	if (name[i].length() == 8)
			cout << left << setw(10)<< id[i] << left << setw(40) << name[i] << left << setw(10) << price[i] << endl;
		else
			cout << left << setw(10) << id[i] << left << setw(40) << name[i] << left << setw(10) << price[i] << endl;
	}
}

void Menu::add()//to add dishes
{
	count++;
	ofstream menu;
	menu.open("menu.txt", ios::app);
	cout << "please input name and price you want to add.(with a blank space in between) " << endl;
	cin >> name[count] >>price[count];
	menu << count <<'\t' << name[count] << '\t'<<price[count];
	menu << endl;
	menu.close();
}
void Menu::modify()//to change name or price of dishes
{
	ofstream menu;
	menu.open("menu.txt");
	int num;
	cout << "Please input the dish ID (The dish you want to modify, or put 0 to exit)" << endl;
	cin >> num;
	while (num != 0)
	{
		if (num < 0 || num > count)
			cout << "The dish ID does not exist" << endl;
		else
		{
			cout << "Please input the dish name (modiyf name)" << endl; 
			string str;
			cin >> str;
			if (str != "0")
			{
				name[num - 1] = "";
				name[num - 1] = str;
			}
			cout << "Please input the price (modify price)" << endl; 
			int p;
			cin >> p;
			if (p != 0)
				price[num - 1] = p;
		}
		
		cout << "Please input the dish ID, or 0 to exit" << endl;
		cin >> num;
	}
	for (int i = 0; i < count; i++)
	{
		if (name[i].length() == 8)
			menu << id[i] << '\t' << name[i] << '\t' << price[i] << endl;
		else
			menu << id[i] << '\t' << name[i] << '\t' << '\t' << price[i] << endl;
	}
	menu.close();
}
void Menu::sub()
{
	ofstream menu;
	menu.open("menu.txt");
	int num;
	cout << "Please input the dish ID (Delete dish)" << endl; //delete dishes
	cin >> num;
	while (num != 0)
	{
		if (num < 0 || num > count)
			cout << "the dish ID does not exist" << endl;
		else
		{
			
			count--;
			cout << "There are (is) " << count << "dish(es) left" << endl;
			for (int i = num - 1; i < count; i++)
			{
				
				name[i] = name[i + 1];
				price[i] = price[i + 1];
			
			}
		}
		cout << "Please input the dish ID (Delete dish)" << endl;
		cin >> num;
	}
	for (int i = 0; i < count; i++)
	{
		if (name[i].length() == 8)
			menu << id[i] << '\t' << name[i] << '\t' << price[i] << endl;
		else
			menu << id[i] << '\t' << name[i] << '\t' << '\t' << price[i] << endl;
	}
	menu.close();
}
void Menu::search()
{
	ifstream menu;
	menu.open("menu.txt");
	int num;
	cout << "Please input the dish ID (Search)" << endl;
	cin >> num;
	while (num != 0)
	{
		if (num < 0 || num > count)
			cout << "The dish ID does not exist" << endl;
		else
		{
			cout << left << setw(10) << "dish ID " << left << setw(40) << "dish name " << left << setw(10) << "price" << endl;
			cout << left << setw(10) << id[num-1] << left << setw(40) << name[num-1] << left << setw(10) << price[num-1] << endl;
			
		}
		cout << "Please input the dish ID"  << endl;
		cin >> num;
	}
	menu.close();
}

#endif
