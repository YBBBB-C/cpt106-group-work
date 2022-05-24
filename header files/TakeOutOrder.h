#pragma once
#ifndef TAKEOUTORDER_H
#define TAKEOUTORDER_H
#include "Menu.h"
#include "Order.h"
using namespace std;
int Inid;
static int outid = 2000;
double daily_interest_o;
double daily_total_o; //daily total income
class TakeOutOrder : public Order
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
	string time;
	string phonenumber;
	string where;
	int year;
	int month;
	int day;
public:
	TakeOutOrder(Date* d);
	void order();
	void print();
};
TakeOutOrder::TakeOutOrder(Date* d)
{
	outid++;
	year = d->get_year();
	month = d->get_month();
	day = d->get_day();
	ifstream outside;
	outside.open("orderid.txt");
	int x, y, z, n;
	outside >> x >> y >> z >> Inid >> n;;
	if (x == year && y == month && z == day)
		outid = n + 1;
	else
		Inid = 1000;
	outside.close();
}
void TakeOutOrder::order()
{
	ofstream outside;
	outside.open("orderid.txt");
	outside << year << '\n' << month << '\n' << day << '\n' << Inid << '\n' << outid;
	outside.close();
	Menu* m;
	m = new Menu;
	m->MENU();
	Raw* r;
	r = new Raw;
	r->RAW();
	int Foodid;
	cout << "Delivery time:" << endl;
	cin >> time;
	cout << "Location:" << endl;
	cin >> where;
	cout << "Your telephone number:" << endl;
	cin >> phonenumber;
	cout << "Please enter the number of the dish you want to order, enter 0 to exit" << endl;
	cin >> Foodid;
	
	while (Foodid != 0)
	{
		if (Foodid < m->count + 1) {

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
			cout << "Ordering ends. No required dish found." << endl;//if input valid number, the ordering system will end automatically.
			break;
		}
	}
	
	
	print();
}
void TakeOutOrder::print()
{
	cout << "------------------------------------------------" << endl;
	cout << "Your order number is£º" << outid << endl;
	cout << "Your dining mode£ºTakeout" << endl;
	cout << "Delivery time£º" << time << endl;
	cout << "Location: " << where << endl;
	cout << "Your telephone number£º" << phonenumber << endl;
	cout << "Delivery price£º" << "2" << endl;
	cout << "Your order is as follows£º" << endl;
	//print titles
	cout <<left<<setw(10) <<"Id" <<left<<setw(40)<<"Dishes" <<left<<setw(15)<< "Price" <<left<<setw(20) << "Count" <<left<<setw(20) << "Total" << endl;
	//print bill list row by row
	for (int i = 0; i < cnt; i++)
	{
		if (name[i].length() == 8)
			cout <<left<<setw(10) <<foodid[i] << left << setw(40) << name[i] << left << setw(20) << price[i] << left << setw(20) << count[i] << left << setw(20) << price[i] * count[i] << endl;
		else
			cout << left << setw(10) << foodid[i] << left << setw(40) << name[i] << left << setw(20) << price[i] << left << setw(20) << count[i] << left<<setw(20) << price[i] * count[i] << endl;
	}
	cout << "Total price is£º" << totalprice + 2 <<"  with 2 yuan as delivery price" << endl;
	daily_total_o += totalprice;
	daily_interest_o += totalinteret;
	cout << "------------------------------------------------" << endl;
	//write file
	string str = itos(year) + '-' + itos(month) + '-' + itos(day) + ".txt";
	ofstream out(str, ios::app);
	out <<"order number: " << outid << endl;
	out << left << setw(20) << "id" << left << setw(40) << "Dishes" << left << setw(15) << "Price" << left << setw(20) << "Count" << left << setw(20) << "Total" << endl;
	for (int i = 0; i < cnt; i++)
	{
		if (name[i].length() == 8)
			out << left << setw(20) << foodid[i] << left << setw(40) << name[i] << left << setw(20) << price[i] << left << setw(20) << count[i] << left << setw(20) << price[i] * count[i] << endl;
		else
			out << left << setw(20) << foodid[i] << left << setw(40) << name[i] << '\t' <<left << setw(20) << price[i] << left << setw(20) << count[i] << left << setw(20) << price[i] * count[i] << endl;
	}
	out << "Total price is£º" << totalprice + 2 << endl;
	total += totalprice + 2;
	daily_interest_o += totalinteret;
	out << "Today's take-out order interest till now is " << daily_interest_o << endl;
	out << "------------------------------------------------" << endl;
	out.close();
}
#endif
