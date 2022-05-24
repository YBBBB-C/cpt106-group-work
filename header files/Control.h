#pragma once
#ifndef CONTROL_H
#define CONTROL_H
#include "InsiderOrder.h"
#include "TakeOutOrder.h"
#include "Date.h"
#include <iostream>
#include <map>
#include"Order.h"
#include"Menu.h"
#include <ctime> 
#include "Raw.h"
#pragma warning( disable : 4996 )
using namespace std;

map<string, string> employee;
map<string, string> manager;

void initial()
{   
    // initialize employee accouts
    ifstream employeestream;
    employeestream.open("employee.txt");

    string employee_account, employee_password;
    while (employeestream >> employee_account >> employee_password)
    {
        employee[employee_account] = employee_password;
    }

    employeestream.close();


    //initialize manager accouts
    ifstream managerstream;
    managerstream.open("manager.txt");

    string manager_account, manager_password;
    while (managerstream >> manager_account >> manager_password)
    {
        manager[manager_account] = manager_password;
    }
    managerstream.close();

}

void modify_employee(string accout, string pwd)
{
    if (employee.find(accout) != employee.end())
    {
        printf("This account has existed\n");
        return;
    }
    employee[accout] = pwd;
    printf("New employee has been added\n");

}
void modify()
{
    ofstream employeestream;
    employeestream.open("employee.txt");
    string employee_account, employee_password;
    for (auto x : employee)
    {
        employeestream << x.first << "    " << x.second << '\n';
    }
    employeestream.close();
}

void Control()
{
    initial();
    int a = 0;
    int b = 0;
    Menu* m;
    m = new Menu;
    m->MENU();

    Raw* r;
    r = new Raw;
    r->RAW();

    int op; // Input content
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);
    Date* d;
    d = new Date(t_tm->tm_year + 1900, t_tm->tm_mon + 1, t_tm->tm_mday);
    cout << "   Today is " << t_tm->tm_year + 1900 << "year" << t_tm->tm_mon + 1 << "month" << t_tm->tm_mday << "day" << endl;
    cout << "   ------------------------------------------------" << endl;
    cout << "           Welcome to Foodie-Park restraunt£¡" << endl;
    cout << "                  How may I help you" << endl;
    cout << "   ------------------------------------------------" << endl;
    cout << " 1: Customer system" << endl;
    cout << " 2: Manager system" << endl;
    cout << " 3: Chef system" << endl;
    cout << " 0: Exit" << endl;
    cout << " Please input£º " << endl;
    cin >> op;
    while (op != 0)
    {
        while (!(op == 1 || op == 2 || op == 3))
        {
            cout << " Wrong input, please input again " << endl;
            cout << " ------------------------------------------------" << endl;
            cout << " 1: Customer system" << endl;
            cout << " 2: Manager system" << endl;
            cout << " 3: Chef system" << endl;
            cout << " 0: Exit" << endl;
            cout << " Please input£º " << endl;
            cin >> op;
        }
        if (op == 1) // The user choosees customer
        {
            cout << "Welcome to the Menu" << endl << endl;
            cout << "------------------------------------------------" << endl;
            m->print();
            cout << "------------------------------------------------" << endl << endl;
            cout << "Eat-in: 1   Takeout: 2   Exit: 0" << endl;
            //choose to eat in or out
            int op_;
            cin >> op_;
            while (!(op_ == 1 || op_ == 2 || op_ == 0))
            {
                cout << "Wrong input, please input again " << endl;
                cout << "------------------------------------------------" << endl;
                cout << "Eat-in:1   Takeout:2   Exit: 0" << endl;
                cin >> op_;
            }
            while (op_ != 0)
            {
                if (op_ == 1) //Customer eat inside
                {
                    a++;
                    InsiderOrder* in;
                    in = new InsiderOrder(d);
                    in->order();
                }
                else if (op_ == 2) //Customer take out food
                {
                    b++;
                    TakeOutOrder* out;
                    out = new TakeOutOrder(d);
                    out->order();
                }
                cout << "Eat-in:1   Takeout:2   Exit: 0" << endl;
                cin >> op_;
            }
            cout << " ------------------------------------------------" << endl;
            cout << " 1: Customer system " << endl;
            cout << " 2: Manager system" << endl;
            cout << " 3: Chef system" << endl;
            cout << " 0: Exit" << endl;
            cout << " Please input £º" << endl;
        }
        else if (op == 2) // The user is a manager
        {
            string account;
            bool power = 0;
            cout << "Your employee account is " << endl;
            cin >> account;
            while (account != "0")
            {
                string password;
                cout << "Your employee password is " << endl;
                cin >> password;

                //identification check
                if (manager.find(account) != manager.end() && manager[account] == password)
                {
                    power = 1;
                    cout << "Login Success" << endl;
                    break;
                }
                else
                {
                    cout << "Your password or account is wrong ! Or, you may choose a wrong system. Please input it again" << endl;
                    cout << "If you want to exist, please input 0" << endl;
                    cout << "Your employee account is" << endl;
                }
                cin >> account;
            }
            //functions in manager system
            if (power)
            {
                bool flag = 1;
                cout << "---------------------------------------------------------------------------" << endl;
                cout << "History order:1  Dish management: 2  Employee management: 3" << endl;
                cout << "Exit: 0" << endl;
                int op;
                cin >> op;
                while (op != 0)
                {
                    if (!(op == 1 || op == 2 || op == 3 || op == 0 ))
                    {
                        cout << "Wrong input, please input again" << endl;
                        cout << "---------------------------------------------------------------------------" << endl;
                        cout << "History order:1  Dish management: 2  Employee management: 3" << endl;
                        cout << "Exit: 0" << endl;
                    }
                    else if (op == 1) //history order:search for order in the pointed day 1
                    {
                        int year, month, day;
                        char c;
                        cout << "Please input the date (Searching date format£º2022 / 5 / 1)" << endl;
                        cin >> year >> c >> month >> c >> day;
                        Date* date = new Date(year, month, day);
                        search(date);
                    }
                    else if (op == 2) // dish management 2
                    {
                        if (flag)
                        {
                            m->print();
                            cout << "---------------------------------------------------------" << endl;
                            r->rprint();
                            flag = 0;
                            cout << "---------------------------------------------------------" << endl;
                        }

                        cout << "Please input:   " << endl;
                        cout << "1: Add dishes" << endl;
                        cout << "2: Modify dishes" << endl;
                        cout << "3: Delete dishes" << endl;
                        cout << "4: Search dishes" << endl;
                        cout << "5: Modify raw materials" << endl;
                        cout << "6: Delete raw materials" << endl;
                        cout << "7: Search raw materials for certain dishes" << endl;
                        cout << "8: add raw material record" << endl;

                        cout << "0: Exit" << endl;
                    

                    int op_;
                    cin >> op_;
                    while (op_ != 0)
                    {
                        if (op_ != 1 && op_ != 2 && op_ != 3 && op_ != 4 && op_ != 5 && op_ != 6 && op_ != 7&&op_!=8)
                        {
                            cout << "Wrong input, please input again" << endl;
                            break;
                        }
                        if (op_ == 1)//add dishes
                        {
                            m->add();
                            m->MENU();
                            m->print();
                            cout << "don't forget to also update materials." << endl;
                        }
                        else if (op_ == 2)//modify dishes
                        {                           
                            m->modify();
                            m->print();
                        }
                        else if (op_ == 3)//delete dishes
                        {
                            m->sub();
                            m->print();
                            cout << "you are recommended to delete the same record of material,to avoid system crashing" << endl;
                            cout << endl;
                        }
                        else if (op_ == 4)//search dishes
                        {
                            m->search();  
                        }

                        else if (op_ == 5)//modify raw material
                        {
                            r->rmodify();
                           
                            r->rprint();
                        }

                        else if (op_ == 6) //delete raw materials
                        {

                            r->rsub();
                            r->rprint();
                            cout << "please double check if the corresponding dish records are removed" << endl;
                            cout << endl;
                        }
                        else if (op_ == 7)
                        {
                            r->rsearch();

                        }
                        else if (op_ == 8)
                        {
                            r->radd();
                            r->RAW();
                            r->rprint();

                        }
                        cout << "Please input :   " << endl;
                        cout << "1: Add dishes" << endl;
                        cout << "2: Modify dishes" << endl;
                        cout << "3: Delete dishes" << endl;
                        cout << "4: Search dishes" << endl;
                        cout << "5: Modify raw materials" << endl;
                        cout << "6: Delete raw materials" << endl;
                        cout << "7: Search raw materials for certain dishes" << endl;
                        cout << "8: add raw material record" << endl;

                        cout << "0: Exit" << endl;
                        cin >> op_;
                    }
                }
                    else if (op == 3) // Add employee id and passward 
                    {
                            string account, passward;
                            cout << " Please input the new employee" << endl;
                            cout << "account\n";
                            cin >> account;
                            cout << "password\n";
                            cin >> passward;
                            modify_employee(account, passward);
                    }
                        cout << "History order:1  Dish management: 2  Employee management: 3" << endl;
                        cout << "Exit: 0" << endl;
                        cin >> op;

                    }
                }
                cout << "------------------------------------------------" << endl;
                cout << "------------------------------------------------" << endl;
                cout << "1: Custom system " << endl;
                cout << "2: Manager system" << endl;
                cout << "3: Chef system" << endl;
                cout << "0: Exit" << endl;
                cout << "please input £º" << endl;
            }
            else if (op == 3) // The user is a chef
            {
                string account;
                bool power = 0;
                cout << "Your employee account is " << endl;
                cin >> account;
                while (account != "0")
                {
                    string password;
                    cout << "Your employee password is " << endl;
                    cin >> password;


                    if (employee.find(account) != employee.end() && employee[account] == password)
                    {
                        power = 1;
                        cout << "Login Success" << endl;
                        break;
                    }
                    else
                    {
                        cout << "Your password is wrong or your employee account is wrong ! Please input it again" << endl;
                        cout << "If you want to exist, please input 0" << endl;
                        cout << "Your employee account is" << endl;
                    }


                    cin >> account;
                }
                if (power)
                {
                    bool flag = 1;
                    cout << "---------------------------------------------------------------------------" << endl;
                    cout << "Dish management: 1 " << endl;
                    cout << "Exit: 0" << endl;
                    int op;
                    cin >> op;
                    while (op != 0)
                    {
                        if (!(op == 1))
                        {
                            cout << "Wrong input, please input again" << endl;
                            cout << "---------------------------------------------------------------------------" << endl;
                            cout << "Dish management: 1 " << endl;
                            cout << "Exit: 0" << endl;
                        }
                        else if (op == 1) // dish management 2
                        {
                            if (flag)
                            {
                                m->print();
                                cout << "---------------------------------------------------------" << endl;
                                r->rprint();
                                flag = 0;
                                cout << "---------------------------------------------------------" << endl;
                            }

                            cout << "Please input:   " << endl;
                            cout << "1: Add dishes" << endl;
                            cout << "2: Modify dishes" << endl;
                            cout << "3: Delete dishes" << endl;
                            cout << "4: Search dishes" << endl;
                            cout << "5: Modify raw materials" << endl;
                            cout << "6: Delete raw materials" << endl;
                            cout << "7: Search raw materials for certain dishes" << endl;
                            cout << "8: add raw material record" << endl;

                            cout << "0: Exit" << endl;


                            int op_;
                            cin >> op_;
                            while (op_ != 0)
                            {
                                if (op_ != 1 && op_ != 2 && op_ != 3 && op_ != 4 && op_ != 5 && op_ != 6 && op_ != 7 && op_ != 8)
                                {
                                    cout << "Wrong input, please input again" << endl;
                                    break;
                                }
                                if (op_ == 1)//add dishes
                                {
                                    m->add();
                                    m->MENU();
                                    m->print();
                                    cout << "your are recommended to update the corresponding materials (enter 8)." << endl;
                                }
                                else if (op_ == 2)//modify dishes
                                {
                                    m->modify();
                                    m->print();
                                }
                                else if (op_ == 3)//delete dishes
                                {
                                    m->sub();
                                    m->print();
                                    
                                    cout << "you are recommended to delete the same record of material,to avoid system crashing" << endl;
                                }
                                else if (op_ == 4)//search dishes
                                {
                                    m->search();
                                }

                                else if (op_ == 5)//modify raw material
                                {
                                    r->rmodify();
                                    r->rprint();
                                }

                                else if (op_ == 6) //delete raw materials
                                {

                                    r->rsub();
                                    r->rprint();
                                    cout << "please double check if the corresponding dish records are removed" << endl;

                                }
                                else if (op_ == 7)
                                {
                                    r->rsearch();

                                }
                                else if (op_ == 8)//add raw material
                                {
                                    r->radd();
                                    r->RAW();
                                    r->rprint();
                                }
                                cout << "Please input :   " << endl;
                                cout << "1: Add dishes" << endl;
                                cout << "2: Modify dishes" << endl;
                                cout << "3: Delete dishes" << endl;
                                cout << "4: Search dishes" << endl;
                                cout << "5: Modify raw materials" << endl;
                                cout << "6: Delete raw materials" << endl;
                                cout << "7: Search raw materials for certain dishes" << endl;
                                cout << "8: add raw material record" << endl;

                                cout << "0: Exit" << endl;
                                cin >> op_;
                            }
                        }
                        cout << "Dish management: 1" << endl;
                        cout << "Exit: 0" << endl;
                        cin >> op;
                    }
                }
                cout << "------------------------------------------------" << endl;
                cout << "------------------------------------------------" << endl;
                cout << "1: custom system " << endl;
                cout << "2: Manager system" << endl;
                cout << "3: Chef system" << endl;
                cout << "0: exit" << endl;
                cout << "please input £º" << endl;
            }
            cin >> op;
        }
        modify();

    }

#endif
