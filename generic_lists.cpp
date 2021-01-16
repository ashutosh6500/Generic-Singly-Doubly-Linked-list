//singly_linked_list- Base class,doubly_list-Derived class
#include<iostream>
#include <unordered_map>
using namespace std;

template<class T>
class singly_linked_list
{
    template<class U>
    class node  //node defination for singly linked list
    {
        public:
            T data;
            node<T> * next;
    };
public:
    singly_linked_list();   //Default constructor
    T data_begin(); //Get data at begin- O(1)
    T data_end();   //Get data at end- O(1)
    void destroy(); //Delete all nodes- O(n)
    long int tot_nodes();   //Get number of nodes- O(1)
    bool search(const T &); //search element- O(1) [Using hashmap]
    virtual void print_list_details();
    virtual void print();   //Print linked list- O(n)
    virtual bool isempty(); //To check emptyness of list- O(1)
    virtual void insert_begin(const T &);   //insert node at begin- O(1)
    virtual void insert_end(const T &);     //insert node at end- O(1)
    virtual void delete_ele(const T &);     //Delete a node with given value- O(n)
    virtual void rotate();  //O(1)
    ~ singly_linked_list();
protected:
    long int cnt;
    node<T> *first,*last;
    unordered_map<T,int>occ;    //Hashmap
};
template<class T>
singly_linked_list<T> ::singly_linked_list()
{
    first=NULL;
    last=NULL;
    cnt=0;
    occ.clear();
}
template<class T>
bool singly_linked_list<T> :: search(const T &a)
{
    if(occ[a])
        return true;
    else
        return false;
}

template<class T>
void singly_linked_list<T> ::insert_begin(const T &a)
{
    occ[a]++;
    cnt++;
    node<T> *newnode;
    newnode=new node<T>;
    newnode->data=a;
    if(isempty())
    {
        first=newnode;
        last=newnode;
    }
    else
    {
        newnode->next=first;
        first=newnode;
    }
}

template<class T>
void singly_linked_list<T> ::insert_end(const T &a)
{
    occ[a]++;
    node<T> *newnode;
    newnode=new node<T>;
    newnode->data=a;
    newnode->next=NULL;
    cnt++;
    if(isempty())
    {
        first=newnode;
        last=newnode;
    }
    else
    {
        last->next=newnode;
        last=newnode;
    }
}

template<class T>
void singly_linked_list<T> :: delete_ele(const T &a)
{
    if(occ[a])
    {
        occ[a]--;
        cnt--;
        if(first->data ==a)
        {
            node<T> * curr=first;
            first=first->next;
            delete curr;
        }
        else
        {
            node<T> *curr,*trail;
            trail=first;
            curr=trail->next;
            while(1)
            {
                if(curr->data ==a)
                {
                    trail->next=curr->next;
                    delete curr;
                    break;
                }
                else
                {
                    trail=curr;
                    curr=curr->next;
                }
            }
        }
    }
    else
        cout<<"Failed delete operation as element is not present\n";
}

template<class T>
void singly_linked_list<T> :: rotate()
{
    if((! isempty()) && (cnt>1))
    {
        T d=first->data;
        node<T> *curr=first;
        first=first->next;
        delete curr;
        insert_end(d);
        occ[d]--;
        cnt--;
    }
}
template<class T>
void singly_linked_list<T> ::print()
{
    node<T> *curr;
    curr=first;
    if(first==NULL)
        cout<<"Empty list\n";
    else
    {
        while(curr!=NULL)
        {
            cout<<curr->data<<" ";
            curr=curr->next;
        }
        cout<<"\n";
    }
}
template<class T>
void singly_linked_list<T> :: print_list_details()
{
    cout<<"linked list details are as follows:\n";
    cout<<"Number of elements : "<<cnt<<"\ncontent: ";
    print();
    if(cnt<=0)
        return;
    else
    {
        cout<<"frequency of each element:\n";
        for(auto w:occ)
        {
            if(w.second)
                cout<<w.first<<" occurs "<<w.second<<" times\n";
        }
    }
}
template<class T>
T singly_linked_list<T> :: data_begin()
{
    if(! isempty())
        return (first->data);
    else
        cout<<"Empty\n";
}
template<class T>
T singly_linked_list<T> :: data_end()
{
    if(! isempty())
        return (last->data);
    else
        cout<<"Empty\n";
}
template<class T>
bool singly_linked_list<T> ::isempty()
{
    return (first==NULL);
}
template<class T>
long int singly_linked_list<T> ::tot_nodes()
{
    return cnt;
}
template<class T>
void singly_linked_list<T> ::destroy()
{
    if(! isempty())
    {
        node<T> *a;
        while(first!=NULL)
        {
            a=first;
            first=first->next;
            delete a;
        }
        cnt=0;
        last=NULL;
    }
    occ.clear();
}

template<class T>
singly_linked_list<T> :: ~ singly_linked_list()
{
    destroy();
}
/****************************************************************************************/
template<class T>
class doubly_list : public singly_linked_list<int>
{
    template<class U>
    class node_2    //node defination for doubly linked list
    {
        public:
            T data;
            node_2<T> * next,*prev;

    };
    node_2<T> *first2,*last2;
    public:
        doubly_list();
        void insert_begin(const T &a);  //insert node at begin- O(1)
        void insert_end(const T &a);    //insert node at end- O(1)
        void delete_ele(const T &a);    //O(n/2)
        void rotate();  //O(1)
        void print();   //O(n)
        bool isempty(); //O(1)
        void print_list_details();//O(n)
};
template<class T>
doubly_list<T> :: doubly_list()
{
    first2=NULL;
    last2=NULL;
}

template<class T>
void doubly_list<T> ::insert_begin(const T &a)
{
    occ[a]++;
    cnt++;
    node_2<T> *newnode;
    newnode=new node_2<T>;
    newnode->next=NULL;
    newnode->prev=NULL;
    newnode->data=a;
    if(isempty())
    {
        first2=newnode;
        last2=newnode;
    }
    else
    {
        newnode->next=first2;
        first2->prev=newnode;
        first2=newnode;
    }
}

template<class T>
void doubly_list<T> ::insert_end(const T &a)
{
    occ[a]++;
    node_2<T> *newnode;
    newnode=new node_2<T>;
    newnode->next=NULL;
    newnode->prev=NULL;
    newnode->data=a;
    cnt++;
    if(isempty())
    {
        first2=newnode;
        last2=newnode;
    }
    else
    {
        last2->next=newnode;
        newnode->prev=last2;
        last2=newnode;
    }
}

template<class T>
void doubly_list<T> :: delete_ele(const T &a)
{
    if(search(a))
    {
        occ[a]--;
        cnt--;
        node_2<T> *itr1,*itr2;
        itr1=first2;
        itr2=last2;
        if(first2->data == a)
        {
            node_2<T> *curr;
            curr=first2;
            first2=first2->next;
            delete curr;
            return;
        }
        else if(last2->data ==a)
        {
            node_2<T> *curr;
            curr=last2;
            last2->prev ->next=NULL;
            last2=last2->prev;
            delete curr;
            return;
        }
        while(1)
        {
            itr1=itr1->next;
            if(itr1->data == a)
            {
                node_2<T> *curr=itr1;
                itr1->prev ->next=itr1->next;
                delete curr;
                break;
            }
            itr2=itr2->prev;
            if(itr2->data ==a)
            {
                node_2<T> *curr=itr2;
                itr2->prev ->next=itr2->next;
                delete curr;
                break;
            }
        }
    }
    else
        cout<<"Given Element is not present in list\n";
}
template<class T>
void doubly_list<T> :: rotate()
{
    if(cnt>1)
    {
        T data1;
        node_2<T> *curr;
        curr=first2;
        data1=first2->data;
        first2=first2->next;
        delete curr;
        insert_end(data1);
        cnt--;
        occ[data1]--;
    }
}
template<class T>
bool doubly_list<T> :: isempty()
{
    return (first2==NULL);
}
template<class T>
void doubly_list<T> ::print()
{
    node_2<T> *curr;
    curr=first2;
    if(first2==NULL)
        cout<<"Empty list\n";
    else
    {
        while(curr!=NULL)
        {
            cout<<curr->data<<" ";
            curr=curr->next;
        }
        cout<<"\n";
    }
}
template<class T>
void doubly_list<T> :: print_list_details()
{
    cout<<"linked list details are as follows:\n";
    cout<<"Number of elements : "<<cnt<<"\ncontent: ";
    print();
    if(cnt<=0)
        return;
    else
    {
        cout<<"frequency of each element:\n";
        for(auto w:occ)
        {
            if(w.second)
                cout<<w.first<<" occurs "<<w.second<<" times\n";
        }
    }
}
/****************************************************************************************/
int main(void)
{
    doubly_list<int> d1;
    singly_linked_list<string>s1;
    for(int r=0;r<16;r++)
    {
        if(r%2==0)
            d1.insert_end(r);
        else
            d1.insert_begin(r);
    }
    d1.print();
    d1.delete_ele(8);
    d1.rotate();
    d1.print_list_details();
    s1.insert_end("Splendid");
    s1.insert_begin("Thousand");
    s1.insert_end("Suns");
    s1.insert_begin("The");
    s1.print();
}
