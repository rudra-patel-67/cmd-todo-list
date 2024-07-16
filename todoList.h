#include <string.h>
using namespace std;

struct Node
{
    bool check=false;
    int no;
    char task[100];
    Node* next;
    Node* prev;
};

class todoList
{
    private :
    Node* head = nullptr;
    Node* tail = nullptr;
    int n=1;

    public :

    Node* createNode(const char* t,int n) {
        Node* newNode = new Node();
        strcpy(newNode->task,t);
        newNode->no=n;
        return newNode;
    }

    void append(const char* t)
    {
        Node* newNode = createNode(t,n);
        n++;
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

        }

        else
        {
            // do
            while (current->no!=x)
            {
                current=current->next;
            } 
            current->prev->next=current->next;
            current->next->prev=current->prev;
            if(current==head)
            {
                head=current->next;
            }
            current->next=current->prev=nullptr;          //DeLINKING current node     
            display();
        }
    }

    void display()
    {
        if(head==nullptr)
        {
            cout<<"List is empty"<<endl;
            return;
        }
        cout << "No.\tX/O\tTasks\n";
        Node* temp = head;
        do
        {
            cout << temp->no << "\t" << (temp->check ? "O" : "X") << "\t" << temp->task << "\n";
            temp = temp->next;
        }
        while(temp!=head);
        cout<<endl;
    }
};
