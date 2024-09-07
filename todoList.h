#ifndef __TODOLIST_H__
#define __TODOLIST_H__

#include <string.h>
// #include "sorting.h" 
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

enum Sort
{
    oldFirst=1,
    recentFirst=2,
    incompleteFirst=3
};

struct Node
{
    bool check=false;
    int no;
    int id;
    char task[100];
    Node* next;
    Node* prev;
};

class todoList
{
    protected: 
    Node* head = nullptr;
    Node* tail = nullptr;

    public :

    int n=1;
    void rearrangingList();
    int choiceForSorting;
    Sort currentSortingState;
    // class sort sort;

    todoList()
    {
        choiceForSorting=oldFirst;
        currentSortingState=oldFirst;
        load();
    }

    ~todoList()
    {
        extract();
    }

    Node* createNode(const char* t,int n,bool c) {
        Node* newNode = new Node();
        strcpy(newNode->task,t);
        newNode->check = c;
        newNode->no=n;
        newNode->id=n;
        return newNode;
    }

    void load() 
    {
        ifstream inFile("toDo.txt");
        
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                // Use a stringstream to parse each line
                istringstream ss(line);
                int no;
                char check;
                string task;

                // Read data from the line into variables
                ss >> no >> check;
                getline(ss >> ws, task);  // Use ws to skip leading whitespace

                bool isChecked = (check == 'O');

                // Create a new node with the parsed data
                Node* newNode = createNode(task.c_str(), no, isChecked);

                if (head == nullptr) {
                    // First node in the list
                    head = newNode;
                    tail = newNode;
                    newNode->next = head;
                    newNode->prev = head;
                } else {
                    // Insert new node at the end and update the circular links
                    tail->next = newNode;
                    newNode->prev = tail;
                    newNode->next = head;
                    head->prev = newNode;
                    tail = newNode;
                }
            }

            inFile.close();
            // std::cout << "Data read from the file successfully." << std::endl;
        } else {
            // std::cerr << "Unable to open the file for reading." << std::endl;
        }
    }

    void extract()
    {
        Node* temp = head;
        choiceForSorting=1;
        // sortBy();
        if (head == nullptr) 
        {
            std::cerr << "List is empty. Nothing to extract." << std::endl;
            return;
        }
        ofstream outFile("toDo.txt");  
        if (outFile.is_open())          // Check if the file is open
        {  
            do
            {
                outFile << temp->no <<"\t"<< (temp->check ? 'O' : 'X') <<"\t"<< temp->task << endl;  // Write to the file
                temp = temp->next;
                // std::cout << "Data written to the file successfully." << std::endl;
            }
            while(temp!=head);
            outFile.close();  // Close the file
        }
        else 
        {
            std::cerr << "Unable to open the file for writing." << std::endl;
        }
    }

    void append(const char* t)
    {
        Node* newNode = createNode(t,n,false);
        if(head==nullptr)
        {
            head = newNode;
            newNode->next = head;
            newNode->prev = head;
        }
        else 
        {
            Node* temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            tail=newNode;
            newNode->next = head;
            
            temp=head;
            while (temp->next!=newNode)
            {
                temp=temp->next;
            }
            newNode->prev=temp;
            head->prev=tail;
        }
        n++;
        display();
    }

    void update()
    {
        int x;
        if(head==nullptr)
        {
            cout<<"List is empty"<<endl;
            return;
        }
        display();
        cout<<"Enter the no. of task to change its state : ";
        cin>>x;
        Node* temp = head;
        bool flag=false;
        do
        {
            if(temp->no==x)
            flag=true;
            temp=temp->next;
        } 
        while (temp!=head);
        if(!flag)
        {
            cout<<"Task No. does not exist in the list"<<endl; 
            return;
        }
        do
        {
            if(temp->no==x)
            (!temp->check)?temp->check=true:temp->check=false;
            temp = temp->next;
        }
        while(temp!=head);
        cout<<endl;
        display();
    }

    void pop()
    {
        display();
        if(head==nullptr)
        {
            cout<<"List is empty"<<endl;
            return;
        }
        int x;
        cout<<"Enter the no. of task you want to delete : ";
        cin>>x;

        //deletion
        Node* current=head;
        
        bool flag=false;
        do
        {
            if(current->no==x)
            flag=true;
            current=current->next;
        } 
        while (current!=head);
        if(!flag)
        {
            cout<<"Invalid Input"<<endl; 
            return;
        }
        if(current->no==x && current->next==current)
        {
            current=head=nullptr;
            cout<<"List is now empty"<<endl;
            n=1;

        }

        else
        {
            // do
            while (current->no!=x)
            {
                current=current->next;
            } 
            n=current->no;
            current->prev->next=current->next;
            current->next->prev=current->prev;
            if(current==head)
            {
                head=current->next;
            }
            Node *temp = current->next;
            do
            {
                temp->no=n;
                n++;
                temp=temp->next;
            }
            while (temp!=head);
            current->next=current->prev=nullptr;          //DeLINKING current node    

            display();
        }
    }

    void display()
    {
        Node* temp = head;
        if (head == nullptr)
        {
            cerr << "List is empty. Nothing to extract." << endl;
            return;
        }

        if(choiceForSorting==1)
        {
            if(currentSortingState!=oldFirst)
            rearrangingList();
            currentSortingState=oldFirst;
            temp = head;
            cout << "\nNo.\tX/O\tTasks\n";
            do
            {
                cout << temp->no << "\t" << (temp->check ? "O" : "X") << "\t" << temp->task << "\n";
                temp = temp->next;
            }
            while(temp!=head);
            cout<<endl;
        }
        else if(choiceForSorting==2)
        {
            if(currentSortingState!=recentFirst)
            rearrangingList();
            currentSortingState=recentFirst;
            temp = tail;
            cout << "\nNo.\tX/O\tTasks\n";
            do
            {
                cout << temp->no << "\t" << (temp->check ? "O" : "X") << "\t" << temp->task << "\n";
                temp = temp->prev;
            }
            while(temp!=tail);
            cout<<endl;
        }
        else if(choiceForSorting==3)
        { 
            if(currentSortingState!=incompleteFirst)
            rearrangingList();
            // currentSortingState=incompleteFirst;
            cout<<"\nIncomplete tasks : \n";
            cout << "No.\tX/O\tTasks\n";
            if(currentSortingState==oldFirst)
            {    
                temp = head;
                do
                {
                    if(temp->check==false)
                    cout << temp->no << "\t" << (temp->check ? "O" : "X") << "\t" << temp->task << "\n";
                    temp = temp->next;
                }
                while(temp!=head);
                cout<<endl<<endl;
                cout<<"Completed tasks :\n";
                cout << "No.\tX/O\tTasks\n";
                do
                {
                    if(temp->check==true)
                    cout << temp->no << "\t" << (temp->check ? "O" : "X") << "\t" << temp->task << "\n";
                    temp = temp->next;
                }
                while(temp!=head);
                cout<<endl;
            }
            if(currentSortingState==recentFirst)
            {    
                temp = tail;
                do
                {
                    if(temp->check==false)
                    cout << temp->no << "\t" << (temp->check ? "O" : "X") << "\t" << temp->task << "\n";
                    temp = temp->prev;
                }
                while(temp!=tail);
                cout<<endl<<endl;
                cout<<"Completed tasks :\n";
                cout << "No.\tX/O\tTasks\n";
                do
                {
                    if(temp->check==true)
                    cout << temp->no << "\t" << (temp->check ? "O" : "X") << "\t" << temp->task << "\n";
                    temp = temp->prev;
                }
                while(temp!=tail);
                cout<<endl;
            }
        }
    }

    void clearList()
    {
        if (head == nullptr) 
        {
            cout<<"List is already empty\n";
            return;
        }
        Node* temp = head;
        do
        {
            Node* nextNode = temp->next;  
            delete temp;                 
            temp = nextNode;              
        }
        while (temp != head);
        head = nullptr; 
        tail = nullptr; 
        n=1;
    }
};

void todoList::rearrangingList()
{
    Node* temp;
    if(choiceForSorting==1)
    {
        temp = head;
        int tempNumber=0;
        do
        {
            tempNumber++;
            temp->no = tempNumber;
            temp = temp->next;
        } 
        while (temp!=head);
    }

    if(choiceForSorting==2) 
    {
        temp = tail;
        int tempNumber=0;
        do
        {
            tempNumber++;
            temp->no = tempNumber;
            temp = temp->prev;
        } 
        while (temp!=tail);
    }

    if(choiceForSorting==3) 
    {
        if(currentSortingState==oldFirst)
        {
            temp = head;
            int tempNumber=0;
            do
            {
                if(temp->check==false)
                {
                    tempNumber++;
                    temp->no = tempNumber;
                }
                temp = temp->next;
            } 
            while (temp!=head);

            do
            {
                if(temp->check==true)
                {
                    tempNumber++;
                    temp->no = tempNumber;
                }
                temp = temp->next;
            } 
            while (temp!=head);
        }
        if(currentSortingState==recentFirst)
        {
            temp = tail;
            int tempNumber=0;
            do
            {
                if(temp->check==false)
                {
                    tempNumber++;
                    temp->no = tempNumber;
                }
                temp = temp->prev;
            } 
            while (temp!=tail);

            do
            {
                if(temp->check==true)
                {
                    tempNumber++;
                    temp->no = tempNumber;
                }
                temp = temp->prev;
            } 
            while (temp!=tail);
        }
    }
}

#endif