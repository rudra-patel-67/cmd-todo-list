#include<iostream>
#include<todoList.h>
using namespace std;

int main()
{
    class todoList td;
    bool end=false;
    char option;
    char task[100];
    int a;
    do
    {
        cout<<"Choose an option to perform"<<endl;
        cout<<"1. Add a Task"<<endl;
        cout<<"2. Delete a Task"<<endl;
        cout<<"3. Update Task"<<endl;
        cout<<"4. Display List"<<endl;
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
        case 'E':
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