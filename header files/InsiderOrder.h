#pragma once
#ifndef INSIDEORDER_H
#define INSIDEORDER_H
#include "Menu.h"
#include "Order.h"
#include"Raw.h"
using namespace std;
static int inid = 1000;
static int tablenumber = 100;
int Outid;
double daily_interest_in;
double daily_total_in; //daily total income

class InsiderOrder : public Order
{
private:
	int id[MAXSIZE] = { 0 };
	string name[MAXSIZE];
	double price[MAXSIZE];
	int count[MAXSIZE];
	int foodid[MAXSIZE];

	string rname[MAXSIZE];            
	double rprice[MAXSIZE];


	double totalprice = 0;
	double totalinteret = 0;
	int cnt = 0;
	int year;
	int month;
	int day;
public:
	InsiderOrder(Date* d);
	void order();
	void print();
};
InsiderOrder::InsiderOrder(Date* d)
{
	inid++;
	year = d->get_year();
	month = d->get_month();
	day = d->get_day();
	ifstream inside;
	inside.open("orderid.txt");
	int x, y, z, m;
	inside >> x >> y >> z >> m >> Outid;
	if (x == year && y == month && z == day)
		inid = m + 1;
	else
		Outid = 2000;
	inside.close();
}
void InsiderOrder::order()
{
	ofstream inside;
	inside.open("orderid.txt");
	inside << year << '\n' << month << '\n' << day << '\n' << inid << '\n' << Outid;
	inside.close();
	Menu* m;
	m = new Menu;
	m->MENU();

	Raw* r;
	r = new Raw;            
	r->RAW();

	int Foodid;
	cout << "Please enter the number of the dish you want to order, enter 0 to exit" << endl;
	cin >> Foodid;


	while (Foodid != 0)
	{
		if (Foodid<m->count+1) {
		
			cout << "Please enter the amount you want to order" << endl;
			cin >> count[cnt];
			id[cnt] = m->id[Foodid - 1];
			name[cnt] = m->name[Foodid - 1];
			
			totalprice += price[cnt] * count[cnt];
			totalinteret += rprice[cnt] * count[cnt];

			foodid[cnt++] = Foodid;
			cout << "Please enter the number of the dish you want to order, enter 0 to exit" << endl;
			cin >> Foodid;
		}
		else {
			cout << "Ordering ends. No required dish found." << endl;
			break;  
		}
	}
	
	print();
}
void InsiderOrder::print()
{
	cout << "Your order number is£º" << inid << endl;
	cout << "Your dining mode is£ºEat-in" << endl;
	cout << "Your table number is£º" << ++tablenumber << endl;
	cout << "Your table charge is£º" << "2" << endl;
	cout << "Your order is as follows£º" << endl;
	//print titles
	cout << left << setw(10) << "Id" << left << setw(40) << "Dishes" << left << setw(15) << "Price" << left << setw(20) << "Count" << left << setw(20) << "Total" << endl;
	//print bill list
	for (int i = 0; i < cnt; i++)
	{
		if (name[i].length() == 8)
			cout << left << setw(10) << foodid[i] << left << setw(40) << name[i] << left << setw(20) << price[i] << left << setw(20) << count[i] << left << setw(20) << price[i] * count[i] << endl;
		else
			cout << left << setw(10) << foodid[i] << left << setw(40) << name[i] << left << setw(20) << price[i] << left << setw(20) << count[i] << left << setw(20) << price[i] * count[i] << endl;
	}
	cout << "Total price is£º" << totalprice+ 2 <<" with 2 yuan as tip" << endl;
	daily_total_in += totalprice;
	daily_interest_in+= totalinteret;

	cout << "------------------------------------------------" << endl;
	
	//write files
	string str = itos(year) + '-' + itos(month) + '-' + itos(day) + ".txt";
	ofstream out(str, ios::app);
	out <<"order number: "<< inid << endl;
	out << left << setw(20) << "id" << left << setw(40) << "Dishes" << left << setw(15) << "Price" << left << setw(20) << "Count" << left << setw(20) << "Total" << endl;
	for (int i = 0; i < cnt; i++)
	{
		if (name[i].length() == 8)
			cout << left << setw(10) << foodid[i] << left << setw(40) << name[i] << left << setw(20) << price[i] << left << setw(20) << count[i] << left << setw(20) << price[i] * count[i] << endl;
		else
			out << left << setw(10) << foodid[i] << left << setw(40) << name[i] << left << setw(20) << price[i] << left << setw(20) << count[i] << left << setw(20) << price[i] * count[i] << endl;
	}
	out << "Total price is£º" << totalprice + 2  << endl;
	total += totalprice + 2;
	daily_interest_in += totalinteret;
	out << "Today's eat-in order interest till now is " << daily_interest_in << endl;
	out << "------------------------------------------------" << endl;
	out.close();
}
#endif
