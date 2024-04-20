#include <bits/stdc++.h>
using namespace std;
template<class T>
class Node
{
public:
    T data;
    Node* nextptr;
};
template<class T>
class linkedlist
{
private:
    Node<T>* head;

public:
    linkedlist()
    {
        head = nullptr;
    }

    bool empty()const
    {
        return (head == nullptr);
    }

    void append_front(const T& value)
    {
        Node<T>* newvalue = new Node<T>();
        newvalue->data = value;

        if (empty())
        {
            newvalue->nextptr = nullptr;
            head = newvalue;
        }
        else
        {
            newvalue->nextptr = head;
            head = newvalue;
        }
    }

    void display()const
    {
        Node<T>* tmp = head;

        while (tmp != NULL)
        {
            cout << tmp->data << " ";
            tmp = tmp->nextptr;
        }
        cout << "\n";
    }

    int count()const
    {
        Node<T>* tmp = head;
        int counter = 0;

        while (tmp != NULL)
        {
            counter++;
            tmp = tmp->nextptr;
        }

        return counter;
    }

    bool search(const T& value)const
    {
        Node<T>* tmp = head;

        while (tmp != NULL)
        {
            if (tmp->data == value)
            {
                return true;
            }
            tmp = tmp->nextptr;
        }

        return false;
    }

    void insert_before(const T& itemvalue, const T& value)
    {
        if (empty())
        {
            append_front(value);
        }
        else if (search(itemvalue))
        {
            Node<T>* newnode = new Node<T>();
            newnode->data = value;
            Node<T>* tmp = head;

            while (tmp->nextptr != nullptr && tmp->data != itemvalue)
            {
                tmp = tmp->nextptr;
            }

            newnode->nextptr = tmp->nextptr;
            tmp->nextptr = newnode;
        }
        else
        {
            cout << "Item is not found\n";
        }
    }

    void append_back(const T& value)
    {
        if (empty())
        {
            append_front(value);
            return;
        }

        Node<T>* newnode = new Node<T>();
        newnode->data = value;
        Node<T>* tmp = head;

        while (tmp->nextptr != NULL)
        {
            tmp = tmp->nextptr;
        }

        newnode->nextptr = nullptr;
        tmp->nextptr = newnode;
    }

    void Delete(const T& itemvalue)
    {
        if (empty())
        {
            cout << "List is empty. No items to delete\n";
            return;
        }

        if (head->data == itemvalue)
        {
            Node<T>* temp = head;
            head = head->nextptr;
            delete temp;
        }
        else
        {
            if (search(itemvalue))
            {
                Node<T>* prev = NULL;
                Node<T>* delptr = head;

                while (delptr->data != itemvalue)
                {
                    prev = delptr;
                    delptr = delptr->nextptr;
                }

                prev->nextptr = delptr->nextptr;
                delete delptr;
            }
            else
            {
                cout << "Item not found in the list. No items to delete\n";
            }
        }
    }
};

template<class T>
int main()
{
    linkedlist<string > lst;

    if (lst.empty())
        cout << "The List is Empty\n";
    else
        cout << "The List contains " << lst.count() << endl;

    string item;

    cout << "Enter Item to insert in the list\n";
    cin >> item;
    lst.append_front(item);
    lst.display();

    cout << "Enter Item to insert in the list\n";
    cin >> item;
    lst.append_front(item);
    lst.display();

    cout << "Enter Item to insert in the list\n";
    cin >> item;
    lst.append_front(item);
    lst.display();

    cout << "The List contains " << lst.count() << endl;

    int newvalue;
    cout << "Enter item to delete\n";
    cin >> item;
    lst.Delete(item);
    lst.display();

}


