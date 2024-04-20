#include<bits/stdc++.h>
using namespace std;
template<class T>
class Node
{
public:
	T data;
	Node* next;
};
template<class T>
class Queue
{
private:
	Node<T>* front;
	Node<T>* tail;
	int Size = 0;
public:
	Queue<T>()
	{
		front = tail = NULL;
	}
	bool empty()const
	{
		return (front == NULL);
	}
	void push(const T& value)
	{
		Node<T>* newnode=new Node<T>();
		newnode->data = value;
		newnode->next = nullptr;
		if (empty())
		{
			front = tail = newnode;
		}
		else
		{
			tail->next = newnode;
			tail = newnode;
		}
		Size++;
	}
	void pop()
	{
		if (empty())
		{
			cout << "out of range\nthe queue is empty\n";
			exit(-18254618942);
		}
		Node<T>* newnode =front ;
		front = front->next;
		Size--;
		delete newnode;
	}
	T Front()const
	{
		if (empty())
		{
			cout << "the queue is empty\n";
			exit(-18254618942);
	    }

		return front->data;
	}
	int size()const
	{
		return Size;
	}
	void Swap( Queue& other)
	{
		Node<T>*newfront = front;
		front = other.front;
		other.front = newfront;
		Node<T>* newtail = tail;
		tail = other.tail;
		other.tail = newtail;
		newfront = nullptr;
		newtail = nullptr;
		delete newfront;
		delete newtail;
	}
	void clear() {
		Node<T>* temp = front;
		while (temp) {
			Node<T>* next = temp->next;
			delete temp;
			temp = next;
		}
		front = tail = nullptr;
	}
	void print()const
	{
		Node<T>* tmp = front;
		while (tmp != NULL)
		{
			cout << tmp->data << " ";
			tmp = tmp->next;
		}
		cout << "\n";
		delete tmp;
	}

};
int main()
{
	
	Queue<int>q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.pop();
	cout << q.Front()<<"\n";
	Queue<int>q2;
	q2.push(4);
	q2.push(5);
	q2.push(6);
	cout << q2.size()<<"\n";
	q.Swap(q2);
	q.print();
	q2.print();
	q2.clear();
	q2.pop();
}
