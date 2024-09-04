#include <string.h>
#include <fstream>
#include <sstream>
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

    Node* createNode(const char* t,int n,bool c) {
        Node* newNode = new Node();
        strcpy(newNode->task,t);
        newNode->check = c;
        newNode->no=n;
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
        cout << "No.\tX/O\tTasks\n";
        do
        {
            cout << temp->no << "\t" << (temp->check ? "O" : "X") << "\t" << temp->task << "\n";
            temp = temp->next;
        }
        while(temp!=head);
        cout<<endl;
    }
    
};
