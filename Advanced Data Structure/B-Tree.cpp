#include <iostream>
#include <vector>
using namespace std;
template <class T, int n>
class B_tree_node {
public:
    vector<T> keys;
    vector<B_tree_node*> children;
    int num;
    bool isLeaf;
    // Constructor initializes a node with a flag indicating if it's a leaf node
    B_tree_node(bool flag = true) : num(0), isLeaf(flag) {
        keys.reserve(n-1);            // Reserve space for keys
        children.reserve(n);     // Reserve space for children (n+1 because non-leaf nodes have n+1 children)
        children.resize(n, nullptr);// Initialize children pointers to null
        keys.resize(n-1,-1);
    }
};


template <class T, int n>
class B_tree {
public:
    B_tree_node<T, n>* root;
    int t;
    B_tree() {
        this->t=n;
        root = nullptr;  // Create the root node as a leaf
    }

    // Split the child node when it is full
    void split(int i, B_tree_node<T, n>* splitter,B_tree_node<T, n>* parent ) {
        B_tree_node<T, n>* new_node = new B_tree_node<T, n>(splitter->isLeaf);
        new_node->num = (t-1)/ 2 ;  // Half the number of keys for the new node
        for (int j = 0; j < (t-1)/ 2 ; j++) {
            new_node->keys[j] = splitter->keys[(t-1) / 2 + j];
        }
        if (!splitter->isLeaf) {
            for (int j = 0; j < t / 2 ; j++) {  // Copy the children of the node
                new_node->children[j] = splitter->children[(t-1) / 2 + j];
            }
        }
        splitter->num = (t-1)/ 2 ;  // Adjust the number of keys in the original node
        // Shift the children of the parent node to make room for the new child
        for (int j = parent->num; j >= i+1 ; j--) {
            parent->children[j + 1] = parent->children[j];
        }
        // Insert the new child into the parent node
        parent->children[i + 1] = new_node;
        // Shift the keys of the parent node to make room for the new key
        for (int j = splitter->num -1 ; j >= 0; j--) {
            splitter->keys[j+1] = splitter->keys[j];
        }
        // Move the middle key from the child to the parent node
        parent->keys[i] = splitter->keys[(t-1) / 2 ];
        parent->num++;

    }

    // Insert key into the current node
    void insert_key(T key, B_tree_node<T, n>* node) {
        int i = node->num - 1;
        if (node->isLeaf) {  // If the node is a leaf, insert the key
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i+1] = key;
            node->num ++;
        } else {  // If the node is not a leaf, insert in the appropriate child
            while (i >= 0 && key < node->keys[i])
                i--;
            i++;
            if (node->children[i]->num == t - 1) {
               split(i, node->children[i] , node);
               node->children[i]->num--;
                if (key > node->keys[i])
                    i++;
            }
            insert_key(key, node->children[i]);
        }
    }

    void insert(T key) {
        if(root== nullptr){
            root = new B_tree_node<T,n>(true);
            root->keys[0]=key;
            root->num++;
        }
        else if (root->isLeaf && root->num==t-1) {
            // If the root is full, create a new root and split the old root
            B_tree_node<T, n>* new_node = new B_tree_node<T, n>(false);  // New non-leaf root
            new_node->children[0] = root;
            split(0, new_node->children[0] , new_node);
            root->num--;
            int i=0;
            if(new_node->keys[0]<key)
                i++;

            insert_key(key, new_node->children[i]);
            root = new_node;
        }
        else
            insert_key(key, root);
    }

    void print(B_tree_node<T, n>* node, int level = 0) {
        if (node == nullptr) return;
        // Indentation for the current level
        for (int i = 0; i < level; i++) {
            cout << "  "; // Two spaces for each level of indentation
        }
        // Print the keys of the current node
        for (int i = 0; i < node->num; i++) {
            cout << node->keys[i] << (i==node->num-1 ? ' ' : ',');
        }
        cout << endl;
        // Recursively print the children if it's not a leaf node
        if (!node->isLeaf) {
            for (int i = 0; i <= node->num; i++) {
                print(node->children[i], level + 1);  // Increase indentation for child nodes
            }
        }
    }
};

int main() {
    B_tree<int, 3> t1;  // Create a B-tree of integers with order 3 (2 keys per node)
    // Insert some keys into the B-tree
    t1.insert(1);
    t1.insert(6);
    t1.insert(0);
    t1.insert(5);
    t1.insert(4);
    t1.insert(2);
    t1.insert(3);
    // Print the tree structure
    t1.print(t1.root);  // Should display the keys in sorted order

    return 0;}