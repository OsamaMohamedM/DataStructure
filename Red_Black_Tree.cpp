#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node* parent;
    char color;

    Node(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        color = 'R';
    };
};

// Class representing a Red-Black Tree
class Red_Black_Tree {
public:
    Node* root;

    Red_Black_Tree() {
        root = nullptr;
    }

    void insert(int data) {
        Node* newnode = new Node(data);
        insert(newnode);
    }


    void print() {
        print(root);
    }

private:

    void print(Node* node) {
        if (node != nullptr) {
            cout << node->data << " " << node->color << "\n";
            print(node->left);
            print(node->right);
        }
    }


    void insert(Node* newnode) {
        Node* x = root;
        Node* y = nullptr;

        // Find the correct position for the new node
        while (x != nullptr) {
            y = x;
            if (newnode->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        newnode->parent = y;

        if (y == nullptr) root = newnode;
        else if (newnode->data < y->data) y->left = newnode;
        else y->right = newnode;

        insert_fixup(newnode);
    }


    void rotate_left(Node* node) {
        Node* y = node->right;
        node->right = y->left;
        if (y->left != nullptr)
            y->left->parent = node;
        y->parent = node->parent;
        if (node->parent == nullptr)
            root = y;
        else if (node == node->parent->left)
            node->parent->left = y;
        else
            node->parent->right = y;
        y->left = node;
        node->parent = y;
    }


    void rotate_right(Node* node) {
        Node* y = node->left;
        node->left = y->right;
        if (y->right != nullptr)
            y->right->parent = node;
        y->parent = node->parent;
        if (node->parent == nullptr)
            root = y;
        else if (node == node->parent->right)
            node->parent->right = y;
        else
            node->parent->left = y;
        y->right = node;
        node->parent = y;
    }


    void insert_fixup(Node* newnode) {
        while (newnode->parent != nullptr && newnode->parent->color == 'R') { // If newnode's parent is a left child
            if (newnode->parent == newnode->parent->parent->left) {
                Node* uncle_newNode = newnode->parent->parent->right; // Get the uncle

                // Case 1: Uncle is red, recolor
                if (uncle_newNode != nullptr && uncle_newNode->color == 'R') {
                    newnode->parent->color = 'B';
                    uncle_newNode->color = 'B';
                    newnode->parent->parent->color = 'R';
                    newnode = newnode->parent->parent; // Move up the tree
                } else {
                    // Case 2: newnode is a right child, rotate left
                    if (newnode == newnode->parent->right) {
                        newnode = newnode->parent;
                        rotate_left(newnode);
                    }
                    // Case 3: Recolor and rotate right
                    newnode->parent->color = 'B';
                    newnode->parent->parent->color = 'R';
                    rotate_right(newnode->parent->parent);
                }
            } else { // Mirror case: newnode's parent is a right child
                Node* uncle_newNode = newnode->parent->parent->left; // the uncle of newnode

                // Case 1: Uncle is red, recolor
                if (uncle_newNode != nullptr && uncle_newNode->color == 'R') {
                    newnode->parent->color = 'B';
                    uncle_newNode->color = 'B';
                    newnode->parent->parent->color = 'R';
                    newnode = newnode->parent->parent; // Move up the tree
                } else {
                    // Case 2: newnode is a left child, rotate right
                    if (newnode == newnode->parent->left) {
                        newnode = newnode->parent;
                        rotate_right(newnode);
                    }
                    // Case 3: Recolor and rotate left
                    newnode->parent->color = 'B';
                    newnode->parent->parent->color = 'R';
                    rotate_left(newnode->parent->parent);
                }
            }
        }

        // Ensure the root is always black
        root->color = 'B';
    }
};

int main() {
    Red_Black_Tree* rbt = new Red_Black_Tree();


    rbt->insert(5);
    rbt->insert(4);
    rbt->insert(1);
    rbt->insert(6);
    rbt->insert(7);
    rbt->insert(2);


    rbt->print();
}
