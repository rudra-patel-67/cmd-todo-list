#include<iostream>
#include<string.h> 
using namespace std;

struct Node
{
    bool check=false;
    int no;
    char task[50];
    Node* next;
    Node* prev;
};

class todoList
{
    private :
    Node* head;
    Node* tail;
    int n=1;

    public :

    todoList()
    {
        head = NULL;
    }

    Node* createNode(const char* t,int n) {
        Node* newNode = new Node();
        strcpy(newNode->task,t);
        newNode->no=n;
        newNode->next = nullptr;
        return newNode;
    }

    void append(const char* t)
    {
        Node* newNode = createNode(t,n);
        n++;
        if(head==NULL)
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
            head->prev=newNode;
        }
        
    }

    void update(int x)
    {
        if(head==NULL)
        {
            cout<<"List is empty"<<endl;
            return;
        }
        Node* temp = head;
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

    void pop(int x)
    {
        if(head==NULL)
        {
            cout<<"List is empty"<<endl;
            return;
        }

        Node* current = tail;
        // // no adjustment below---------------------------THIS IS NOW WORKING PROPERLY
        // do
        // {
        //     current->no=current->prev->no;
        //     current=current->prev;
        // } 
        // while (current->no!=x);


        // if(current==head)
        // {
        //     head=current->next;

        // }
        // else
        // {
        // }

        //deletion-------------------------------------NEED TO WORK ON FIRST AND LAST DELETION
        current=head;
        // if(current->no==x)
        // { 
        //     // cout<<tail->prev<<"\t"<<tail->no<<"\t"<<tail->next<<"\t"<<endl;
        //     // cout<<head->prev<<"\t"<<head->no<<"\t"<<head->next<<"\t"<<endl;
        //     // tail->next=current->next;
        //     // current->next->prev=tail;
        //     current->prev=current->next=NULL;          //DeLINKING current node        
        // }

        // else
        
        // else
        // {    
        do
        {
            current=current->next;
        } 
        while (current->no!=x);
        current->prev->next=current->next;
        current->next->prev=current->prev;
        current->next=current->prev=NULL;          //DeLINKING current node     
        display();
        // }
    }

    void test()
    {
        Node* current = head;
        do
        {
            cout<<current->prev<<"\t"<<current->no<<"\t"<<current->next<<"\t"<<endl;
            current=current->next;
        } while (current!=head);
        
    }

    void display()
    {
        if(head==NULL)
        {
            cout<<"List is empty"<<endl;
            return;
        }
        cout << "No.\tX/O\tTasks\n";
        Node* temp = head;
        do
        {
            cout << temp->no << "\t";
            (temp->check)?cout<<"O\t" : cout<<"X\t";
            cout<<temp->task<< "\n";
            temp = temp->next;
        }
        while(temp!=head);
        cout<<endl;
    }
};

int main()
{
    class todoList td;
    bool end=false;
    char option;
    char task[50];
    int a;
    td.append("1");
    td.append("2");
    td.append("3");
    td.append("4");
    do
    {
        cout<<"Choose an option to perform"<<endl;
        cout<<"1. Add a Task"<<endl;
        cout<<"2. Delete a Task"<<endl;
        cout<<"3. Update Task"<<endl;
        cout<<"4. Display List"<<endl;
        cout<<"E. Exit"<<endl<<endl;
        cin>>option;
        system("cls");
        switch (option)
        {
        case '1':
            // cout<<"Task : ";
            // cin>>task;
            // td.append(task);
            cout<<"Task added!"<<endl<<endl;
            break;
        case '2':
            td.display();
            cout<<"Enter the no. of task you want to delete : ";
            cin>>a;
            td.pop(a);
            break;
        case '3':
            td.display();
            cout<<"Enter the no. of task to change its state : ";
            cin>>a;
            td.update(a);
            break;
        case '4':
            td.display();
            break;
        case '5':
            td.test();
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