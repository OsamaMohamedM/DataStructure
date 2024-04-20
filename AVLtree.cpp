#include <iostream>
using namespace std;
template<class T>
class node {
public:
    T data;
   node<T>* left, right;
    node(const T& data)
    {
        left = right = NULL;
        this->data = data;
    }
    int hight;
};
template <class T>
class avl {
private:
    node<T>* root;
public:
    int getbalance(node<T>*r)
    {
        if (r == NULL)
            return 0;
        return r->left->hight - r->right->hight;
    }
    node<T>* rightrotation(node<T>*&r)
    {
        node<T>*x = r->left;
        node<T>* y = x->right;

        x->right = r;
        r->left = y;

        r->hight = max(r->right->hight, r->left->hight);
        x->hight = max(x->right->hight, x->left->hight);

        y = NULL;
        delete y;
        return x;
    }
    node<T>* leftrotation(node<T>*& r)
    {
        node<T>* x = r->right;
        node<T>* y = x->left;

        x->left = r;
        r->right = y;

        r->hight = max(r->right->hight, r->left->hight);
        x->hight = max(x->right->hight, x->left->hight);

        y = NULL;
        delete y;

        return x;
    }
   node<T>* insert(node<T>* r, T value)
    {

        if (root == NULL)
        {
            node<T>newnode = new node<T>(value);
            root = newnode;
        }
        else if (value > r->data)
        {
            node<T>newnode = new node<T>(value);
           r->right= insert(r->right, value);
        }
        else if (r->data > value)
        {
            node<T>newnode = new node<T>(value);
           r->left= insert(r->left, value);
        }
        else
        {
            return r;
        }
        r->hight = max(r->left->hight, r->right->hight) + 1;
        int k = getbalane(r);
        //left left
        if (k > 1 && r->left->data > value)
        {
          r= rightrotation(r);
          return r;
        }
        // left Right
        if (k > 1 && r->left->data < value)
        {
            r->left = leftrotaion(r->left);
            r = rightrotation(r);
            return r;
        }
        // Right left
        if (k<-1 && r->right->data>vlaue)
        {
            r->right = rightrotaion(r->right);
            r = leftrotation(r);
            return r;
        }
        //Right Right
        if (k < -1 && r->right->data < vlaue)
        {
            r = leftrotaion(r);
            return r;
        }
        return r;
    }
};
int main()
{
    
}

