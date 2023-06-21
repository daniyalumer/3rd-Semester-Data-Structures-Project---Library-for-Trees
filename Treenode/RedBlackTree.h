// Implementing Red-Black Tree in C++

#include <iostream>
#include"BinaryTree.h"
#define SPACE 10
using namespace std;
template <class T>
class tnode :public BinaryTree<T>{
public:
    T data;
    tnode<T>* parent;
    tnode<T>* left;
    tnode<T>* right;
    int color;
};
template <class T>
class RedBlackTree {
private:
    tnode<T>* root;
    tnode<T>* TNULL;

    void NULLNode(tnode<T>* node,tnode<T>* parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    // Preorder
    void preOrder(tnode<T>* node) {
        if (node != TNULL) {
            cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    // Inorder
    void inOrder(tnode<T>* node) {
        if (node != TNULL) {
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }
    }

    // Post order
    void postOrder(tnode<T>* node) {
        if (node != TNULL) {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->data << " ";
        }
    }

    tnode<T>* searchTreeH(tnode<T>* node, T key) {
        if (node == TNULL || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeH(node->left, key);
        }
        return searchTreeH(node->right, key);
    }

    // For balancing the tree after deletion
    void deleteFix(tnode<T>* x) {
        tnode<T>* s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void rbTransplant(tnode<T>* u, tnode<T>* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelp(tnode<T>* node, T key) {
        tnode<T>* z = TNULL;
        tnode<T>* x;
        tnode<T>* y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            deleteFix(x);
        }
    }

    // For balancing the tree after insertion
    void insertFix(tnode<T>* k) {
        tnode<T>* u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void printH(tnode<T>* root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")" << endl;
            printH(root->left, indent, false);
            printH(root->right, indent, true);
        }
    }

public:
    RedBlackTree() {
        TNULL = new tnode<T>;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void preorder() {
        preOrder(this->root);
    }

    void inorder() {
        inOrder(this->root);
    }

    void postorder() {
        postOrder(this->root);
    }

    tnode<T>* SearchTree(int k) {
        return searchTreeH(this->root, k);
    }

    tnode<T>* minimum(tnode<T>* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    tnode<T>* maximum(tnode<T>* node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    tnode<T>* successor(tnode<T>* x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        tnode<T>* y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    tnode<T>* predecessor(tnode<T>* x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        tnode<T>* y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(tnode<T>* x) {
        tnode<T>* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(tnode<T>* x) {
        tnode<T>* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(int key) {
        tnode<T>* node = new tnode<T>;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        tnode<T>* y = nullptr;
        tnode<T>* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->data < y->data) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFix(node);
    }

    tnode<T>* getRoot() {
        return this->root;
    }

    void deleteNode(int data) {
        
        deleteNodeHelp(this->root, data);
    }

    void printTree() {
        if (root) {
            printH(this->root, "", true);
        }
    }
    void print2D(tnode<T>* r, int space)
    {
        if (r->data ==TNULL->data)
            return;
        space += SPACE;
        print2D(r->right, space);
        std::cout << std::endl;
        for (int i = SPACE; i < space; i++)
            std::cout << " ";
        string sColor = r->color ? "RED" : "BLACK";
        cout << r->data << "(" << sColor << ")" << endl;
        print2D(r->left, space);

    }
};
