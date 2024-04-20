#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;
template<class T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;
};

template<class T>
class CircularDoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    CircularDoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void insertAtHead(const T& data) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        if (head == nullptr) {
            head = tail = newNode;
            tail->next = head;
            head->prev = tail;
        }
        else {
            newNode->next = head;
            tail->next = newNode;
            head = newNode;
            head->prev = tail;
        }
        size++;
    }

    void insertAtTail(const T& data) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        if (tail == nullptr) {
            head = tail = newNode;
            tail->next = head;
            head->prev = tail;
        }
        else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
            head->prev = tail;
        }
        size++;
    }

    void insertAt(const T& data, int index) {
        if (index < 0 || index > size) {
            throw out_of_range("Index out of range");
        }
        if (index == 0)
            insertAtHead(data);
        else if (index == size)
            insertAtTail(data);
        else {
            Node<T>* tmp = head;
            for (int i = 0; i < index - 1; ++i) {
                tmp = tmp->next;
            }
            Node<T>* newNode = new Node<T>();
            newNode->data = data;
            newNode->next = tmp->next;
            tmp->next->prev = newNode;
            tmp->next = newNode;
            newNode->prev = tmp;
            size++;
            tmp = NULL;
            delete tmp;
        }
    }

    

    void removeAtHead() {
        if (head == nullptr) {
            throw out_of_range("List is empty");
        }
        Node<T>* tmp = head;
        if (size == 1)
            head = tail = nullptr;
        else
        {

            head = head->next;
            tail->next = head;
            head->prev = tail;

        }
        delete tmp;
        size--;
    }

    void removeAtTail() {
        if (tail == nullptr) {
            throw out_of_range("List is empty");
        }
        Node<T>* tmp = tail;

        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        delete tmp;
        size--;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        if (index == 0)
            removeAtHead();
        else if (index == size - 1)
            removeAtTail();
        else {
            Node<T>* tmp = head;
            for (int i = 0; i < index - 1; ++i) {
                tmp = tmp->next;
            }
            Node<T>* tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            tmp->next->prev = tmp;
            tmp = NULL;
            delete tmp;
            delete tmp2;
        }
        size--;
    }
    T retrieve(int index)
    {
        unique_ptr<Node<T>> tmp = make_unique<Node<T>>(*head);
        while (index--)
        {
            tmp = tmp->next;
        }

        return tmp->data;
    }

    void Swap(int idx1, int idx2)
    {
        if (idx1 == idx2)
            return;
        if (idx1 > idx2)swap(idx1, idx2);
        Node<T>* tmp = head;
        Node<T>* prev = tail;
        Node<T>* next = head->next;

        for (int i = 0; i < idx1; ++i) {
            prev = tmp;
            tmp = tmp->next;
            next = tmp->next;
        }

        Node<T>* tmp2 = head;
        Node<T>* prev2 = tail;
        Node<T>* next2 = head->next;
        for (int i = 0; i < idx2; ++i) {
            prev2 = tmp2;
            tmp2 = tmp2->next;
            next2 = tmp2->next;
        }
        if (idx2 - idx1 == 1)
        {
            if (size == 2)
            {
                head = tail;

                tail = tmp;
            }
            else {

                tmp2->next = tmp;
                tmp->next = next2;
                tmp2->prev = prev;
                tmp->prev = tmp2;
                next2->prev = tmp;
                prev->next = tmp2;
                if (idx1 == 0)
                {
                    tmp2->prev = tail;
                    tail->next = tmp2;
                    head = tmp2;
                }
                if (idx2 == size - 1)
                {
                    tmp->next = head;
                    head->prev = tmp;
                    tail = tmp;
                }
            }


        }
        else if (idx2 == size - 1 && idx1 == 0)
        {
            tmp2->next = tmp->next;
            tmp->next = tmp2;
            prev2->next = tmp;
            tail = tmp;
            head = tmp2;
            head->prev = tail;
            tail->next = head;

        }
        else
        {

            tmp->next = next2;
            tmp2->next = next;
            prev->next = tmp2;
            tmp2->prev = prev;
            prev2->next = tmp;
            tmp->prev=prev2;
        }


    }

    void replace(const T& data, int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Node<T>* tmp = head;
        for (int i = 0; i < index; ++i) {
            tmp = tmp->next;
        }
        tmp->data = data;
    }

    bool isExist(const T& data) {
        unique_ptr<Node<T>> tmp = make_unique<Node<T>>(*head);
        while (tmp != nullptr) {
            if (tmp->data == data) {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

    bool isItemAtEqual(const T& data, int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return data == retrieve(index);
    }

    bool isEmpty() {
        return size == 0;
    }

    int linkedListSize() {
        return size;
    }

    void clear() {
  
        while (size--) {
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        size = 0;
    }

    void print() {
        Node<T>* tmp = head;
        int  cnt = 0;
        while (cnt++ < size) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << "\n";
        tmp = NULL;
        delete tmp;
    }


    Node<T>*& Head()
    {
        return head;
    }
};



int main() {
  

    return 0;
}
