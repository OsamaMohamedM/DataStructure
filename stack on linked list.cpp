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
class Stack
{
private:
	Node<T>* top;
	Node<T>* tail;
	int Size = 0;
public:
	Stack<T>()
	{
		top = tail = NULL;
	}
	bool empty()const
	{
		return (top == NULL);
	}
	void push(const T& value)
	{
		Node<T>* newnode = new Node<T>();
		newnode->data = value;
		newnode->next = nullptr;
		if (empty())
		{
			top = tail = newnode;
		}
		else
		{
			newnode->next = top;
			top = newnode;
		}
		Size++;
	}
	void pop()
	{
		if (empty())
		{
			cout << "out of range\nthe Stack is empty\n";
			exit(-18254618942);
		}
		Node<T>* newnode = top;
		top = top->next;
		Size--;
		delete newnode;
	}
	T Top()const
	{
		if (empty())
		{
			cout << "the Stack is empty\n";
			exit(-18254618942);
		}

		return top->data;
	}
	int size()const
	{
		return Size;
	}
	void Swap(Stack& other)
	{
		Node<T>* newtop = top;
		top = other.top;
		other.top = newtop;
		Node<T>* newtail = tail;
		tail = other.tail;
		other.tail = newtail;
		newtop = nullptr;
		newtail = nullptr;
		delete newtop;
		delete newtail;
	}
	void clear() {
		Node<T>* temp = top;
		while (temp) {
			Node<T>* next = temp->next;
			delete temp;
			temp = next;
		}
		top = tail = nullptr;
	}
	void print()const
	{
		Node<T>* tmp = top;
		while (tmp != NULL)
		{
			cout << tmp->data << " ";
			tmp = tmp->next;
		}
		cout << "\n";
		delete tmp;
	}

};
int priority(const char& exp)
{
	if (exp == '+' || exp == '-')
		return 1;
	if (exp == '*' || exp == '/')
		return 2;
	if (exp == '^')
		return 3;
	return 0;
}
string convertInfixToPostfix(const string& expression)
{
	int sz = expression.size();
	Stack<int>stk;
	string finalExpression;
	for (int i = 0; i < sz; i++)
	{
		if (isdigit(expression[i]) || isalpha(expression[i]))
			finalExpression += expression[i];
		else if (expression[i]=='(')
			stk.push(expression[i]);
		else if (expression[i] == ')')
		{
			while (!stk.empty() && stk.Top() != '(')
			{
				finalExpression += stk.Top();
				stk.pop();
			}
			stk.pop();
		}
		else
		{
			while (!stk.empty() && priority(expression[i]) <= priority(stk.Top()))
			{
				finalExpression += stk.Top();
				stk.pop();
			}
			stk.push(expression[i]);
		}
	}
	while (!stk.empty())
	{
		finalExpression += stk.Top();
		stk.pop();
	}
	return finalExpression;
}


string convertInfixToPrefix(string expression)
{
	int n = expression.size();

	reverse(expression.begin(), expression.end());

	for (int i = 0; i < n; i++) {

		if (expression[i] == '(') {
			expression[i] = ')';
		}
		else if (expression[i] == ')') {
			expression[i] = '(';
		}
	}

	string finalexpression =convertInfixToPostfix(expression);
	reverse(finalexpression.begin(), finalexpression.end());

	return finalexpression;
}
int main()
{
	cout << convertInfixToPostfix("(1+2)^3-3+((6*7/5)+1)-2")<<"\n";
	cout << convertInfixToPrefix("(1+2)^3-3+((6*7/5)+1)-2");
	
}
