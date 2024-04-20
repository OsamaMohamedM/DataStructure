#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;
template<class T>
class Node {
public:
    T data;
    Node* next;
};

template<class T>
class CircularSingleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    CircularSingleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void insertAtHead(const T& data) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = tail = newNode;
            tail->next = head;
        }
        else {
            newNode->next = head;
            tail->next = newNode;
            head = newNode;
        }
        size++;
    }

    void insertAtTail(const T& data) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = nullptr;

        if (tail == nullptr) {
            head = tail = newNode;
            tail->next = head;
        }
        else {

            tail->next = newNode;
            tail = newNode;
            tail->next = head;
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
            tmp->next = newNode;
            size++;
            tmp = NULL;
            delete tmp;
        }
    }

    void insertAfter(Node<T>* tmp, const T& data)
    {


        Node<T>* newNode = new Node<T>();
        newNode->data = data;

        newNode->next = tmp->next;
        tmp->next = newNode;
        size++;
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

        }
        delete tmp;
        size--;
    }

    void removeAtTail() {
        if (tail == nullptr) {
            throw out_of_range("List is empty");
        }
        Node<T>* tmp = head;
        while (tmp->next != tail && tmp != tail)
            tmp = tmp->next;

        tail = tmp;
        tail->next = head;
        tmp = tmp->next;
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

        for (int i = 0; i < idx1 ; ++i) {
            prev = tmp;
            tmp = tmp->next;
            next = tmp->next;
        }

        Node<T>* tmp2 = head;
        Node<T>* prev2 = tail;
        Node<T>* next2 = head->next;
        for (int i = 0; i < idx2 ; ++i) {
             prev2 = tmp2;
            tmp2 = tmp2->next;
            next2 = tmp2->next;
        }
        if (idx2 - idx1 == 1 )
        {
            if (size == 2)
            {
                head = tail;
                tail = tmp;
            }
            else {

            tmp2->next = tmp;
            tmp->next = next2;
            prev->next = tmp2;
            }
            

        }
        else if (idx2 == size - 1 && idx1 == 0)
        {
            tmp2->next = tmp->next;
            tmp->next = tmp2;
            prev2->next = tmp;
            tail = tmp;
            head = tmp2;
            
        }
        else
        {

            tmp->next = next2;
            tmp2->next = next;
            prev->next = tmp2;
            prev2->next = tmp;
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
        while (head != nullptr) {
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
        while (cnt++<size ) {
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
    CircularSingleLinkedList<> list;

    return 0;
}
