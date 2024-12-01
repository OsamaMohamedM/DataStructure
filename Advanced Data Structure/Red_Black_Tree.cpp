#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* left;
    Node* right;
    Node* parent;
    char color;

    Node(T data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        color = 'R';
    }
};

template <typename T>
class Red_Black_Tree {
public:
    Red_Black_Tree() {
        root = nullptr;
    }

    void insert(T data) {
        Node<T>* newnode = new Node<T>(data);
        insert(newnode);
    }

    void deleteNode(T data) {
        deleteNode(root, data);
    }

    void print() {
        print(root);
    }

private:
    Node<T>* root;

    void print(Node<T>* node) {
        if (node != nullptr) {
            cout << node->data << " " << node->color << "\n";
            print(node->left);
            print(node->right);
        }
    }

    void insert(Node<T>* newnode) {
        Node<T>* x = root;
        Node<T>* y = nullptr;

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

    void rotate_left(Node<T>* node) {
        Node<T>* y = node->right;
        node->right = y->left;
        if (y->left != nullptr)
            y->left->parent = node;
        y->parent = node->parent;
        if (node->parent == nullptr)
            root = y;  // If node is root
        else if (node == node->parent->left)
            node->parent->left = y;
        else
            node->parent->right = y;
        y->left = node;
        node->parent = y;
    }

    void rotate_right(Node<T>* node) {
        Node<T>* y = node->left;
        node->left = y->right;
        if (y->right != nullptr)
            y->right->parent = node;
        y->parent = node->parent;
        if (node->parent == nullptr)
            root = y;  // If node is root
        else if (node == node->parent->right)
            node->parent->right = y;
        else
            node->parent->left = y;
        y->right = node;
        node->parent = y;
    }

    void insert_fixup(Node<T>* newnode) {
        while (newnode->parent != nullptr && newnode->parent->color == 'R') {
            if (newnode->parent == newnode->parent->parent->left) {
                Node<T>* uncle_newNode = newnode->parent->parent->right;

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
                Node<T>* uncle_newNode = newnode->parent->parent->left;

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

    void deleteNode(Node<T>* node, T key) {
        Node<T>* z = nullptr;
        Node<T>* x, * succsessor;
        while (node != nullptr) {
            if (node->data == key) {
                z = node;
                break;
            }

            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == nullptr) {
            cout << "Key not found in the tree" << '\n';
            return;
        }

        char y_original_color = z->color;
        if (z->left == nullptr) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            succsessor = getSuccessor(z->right);
            y_original_color = succsessor->color;
            x = succsessor->right;
            if (succsessor->parent == z) {
                if (x) x->parent = succsessor;
            } else {
                rbTransplant(succsessor, succsessor->right);
                succsessor->right = z->right;
                succsessor->right->parent = succsessor;
            }
            rbTransplant(z, succsessor);
            succsessor->left = z->left;
            succsessor->left->parent = succsessor;
            succsessor->color = z->color;
        }
        delete z;
        if (y_original_color == 'B') {
            deleteFix(x);
        }
    }

    void rbTransplant(Node<T>* u, Node<T>* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void deleteFix(Node<T>* DB) {
        while (DB != root && (DB == nullptr || DB->color == 'B')) {
            if (DB == DB->parent->left) {
                Node<T>* brother = DB->parent->right;
                if (brother->color == 'R') {
                    swap(brother->color, DB->parent->color);
                    rotate_left(DB->parent);
                    brother = DB->parent->right;
                }
                if ((brother->left == nullptr || brother->left->color == 'B') &&
                    (brother->right == nullptr || brother->right->color == 'B')) {
                    brother->color = 'R';
                    DB = DB->parent;
                } else {
                    if (brother->right == nullptr || brother->right->color == 'B') {
                        if (brother->left != nullptr) brother->left->color = 'B';
                        brother->color = 'R';
                        rotate_right(brother);
                        brother = DB->parent->right;
                    }
                    swap(DB->parent->color, brother->color);
                    rotate_left(DB->parent);
                    if (brother->right != nullptr) brother->right->color = 'B';
                    DB = root;
                }
            } else {
                Node<T>* w = DB->parent->left;
                if (w->color == 'R') {
                    w->color = 'B';
                    DB->parent->color = 'R';
                    rotate_right(DB->parent);
                    w = DB->parent->left;
                }
                if ((w->right == nullptr || w->right->color == 'B') &&
                    (w->left == nullptr || w->left->color == 'B')) {
                    w->color = 'R';
                    DB = DB->parent;
                } else {
                    if (w->left == nullptr || w->left->color == 'B') {
                        if (w->right != nullptr) w->right->color = 'B';
                        w->color = 'R';
                        rotate_left(w);
                        w = DB->parent->left;
                    }
                    w->color = DB->parent->color;
                    DB->parent->color = 'B';
                    if (w->left != nullptr) w->left->color = 'B';
                    rotate_right(DB->parent);
                    DB = root;
                }
            }
        }
        if (DB != nullptr) DB->color = 'B';
    }

    Node<T>* getSuccessor(Node<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};

int main() {
    Red_Black_Tree<int>* rbt = new Red_Black_Tree<int>();
    rbt->insert(10);
    rbt->insert(5);
    rbt->insert(15);
    rbt->insert(1);
    rbt->insert(6);
    rbt->print();

    cout << "Deleting 6...\n";
    rbt->deleteNode(6);
    rbt->print();

    return 0;
}
