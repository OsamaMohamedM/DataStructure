#include <iostream>
using namespace std;

template <class T>
class node {
public:
    T data;
    node<T>* left;
    node<T>* right;

    node(const T& data) {
        left = right = NULL;
        this->data = data;
    }
};

template <class T>
class BST {
private:
    node<T>* root;

    node<T>* insert(node<T>* r, T value) {
        if (r == NULL)
            return new node<T>(value);

        if (value < r->data)
            r->left = insert(r->left, value);
        else if (value > r->data)
            r->right = insert(r->right, value);

        return r;
    }

    node<T>* findMin(node<T>* r) {
        while (r->left != NULL)
            r = r->left;
        return r;
    }

    node<T>* deleteNode(node<T>* r, T value) {
        if (r == NULL)
            return r;

        if (value < r->data)
            r->left = deleteNode(r->left, value);
        else if (value > r->data)
            r->right = deleteNode(r->right, value);
        else {
            if (r->left == NULL) {
                node<T>* temp = r->right;
                delete r;
                return temp;
            } else if (r->right == NULL) {
                node<T>* temp = r->left;
                delete r;
                return temp;
            }

            node<T>* temp = findMin(r->right);
            r->data = temp->data;
            r->right = deleteNode(r->right, temp->data);
        }
        return r;
    }

    void inorder(node<T>* r) {
        if (r != NULL) {
            inorder(r->left);
            cout << r->data << " ";
            inorder(r->right);
        }
    }

public:
    BST() {
        root = NULL;
    }

    void insert(T value) {
        root = insert(root, value);
    }

    void deleteNode(T value) {
        root = deleteNode(root, value);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {


    return 0;
}
