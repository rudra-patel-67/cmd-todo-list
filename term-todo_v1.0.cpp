#include<iostream>
#include<conio.h>
#include"todoList.h"
using namespace std;

int main()
{
    class todoList td;
    bool end=false;
    char option;
    char choiceForClear;
    char task[100];
    int a;
    td.load();
    do
    {
        cout<<"Choose an option to perform"<<endl;
        cout<<"1. Add a Task"<<endl;
        cout<<"2. Delete a Task"<<endl;
        cout<<"3. Update Task"<<endl;
        cout<<"4. Display List"<<endl;
        cout<<"5. Clear List"<<endl;
        cout<<"6. Change Sorting of List"<<endl;
        cout<<"E. Exit"<<endl<<endl;
        cin>>option;
        cin.ignore();
        system("cls");
        switch (option)
        {
        case '1':
            cout<<"Task : ";
            cin.getline(task,100);
            td.append(task);
            cout<<"Task added!"<<endl<<endl;
            break;
        case '2':
            td.pop();
            break;
        case '3':
            td.update();
            break;
        case '4':
            td.display();
            break;
        case '5':
            cout<<"Warning : \nThis will clear the To-Do list. Do you wish to continue (y/n) :";
            cin>>choiceForClear;
            if(choiceForClear=='y'||choiceForClear=='Y')
            {
                td.clearList();
                cout<<"List cleared\n"<<endl;
            }
            break;
        case '6':   
            cout<<"Sort by : "<<endl;
            cout<<"1. Oldest First"<<endl;
            cout<<"2. Recent First"<<endl;
            cout<<"3. Incomplete task first"<<endl;
            cin >>td.choiceForSorting;
            // td.sortBy();
            td.display();
            break;
        case 'E':
        case 'e':
            end=true;
            break;
        default:
            cout<<"Invalid Input"<<endl;
            break;
        }   
    }
    while(!end);
    return 0;
}