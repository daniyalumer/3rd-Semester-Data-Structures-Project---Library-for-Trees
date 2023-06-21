#pragma once
#include <iostream>
#include"BinaryTree.h"
#include"TNode.h"
using namespace std;
#define SPACE 10
template<class T>
class AVLTree :public BinaryTree<T> {
private:
    TNode<T>* root;
    T max(T a, T b);
    int height(TNode<T>* N);
    void clearAll(TNode<T>* c);
   

public:
    AVLTree() {
        root = nullptr;
    }
    AVLTree(T data){
      TNode<T>* root = new TNode<T>(data,NULL,NULL);
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        root->height = 1;
    }
    ~AVLTree() {clearAll(this->root);}
    TNode<T>* rightRotate(TNode<T>* y);
    TNode<T>* leftRotate(TNode<T>* x);
    int BalanceFactor(TNode<T>* N);
    TNode<T>* insertNode(TNode<T>* node,T k);
    TNode<T>* nodeWithMimumValue(TNode<T>* node);
    TNode<T>* deleteNode(TNode<T>* root, T k);
    void printTree(TNode<T>* root, string indent, bool last);
    void print2D(TNode<T>* r, int space);
};
template<class T>
void AVLTree<T>::clearAll(TNode<T>* c) {
    if (c == nullptr) return;
    clearAll(c->left);
    clearAll(c->right);
    delete c;
}



template<class T>
T AVLTree<T>::max(T a, T b) {
    return (a > b) ? a : b;
}



template<class T>
int AVLTree<T>::height(TNode<T>* N) {
    if (N == NULL)
        return 0;
    return N->height;

}
template<class T>
TNode<T>* AVLTree<T>::rightRotate(TNode<T>* y) {

    TNode<T>* x = y->left;
    TNode<T>* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
        height(y->right)) +
        1;
    x->height = max(height(x->left),
        height(x->right)) +
        1;
    return x;

}
template<class T>
TNode<T>* AVLTree<T>::leftRotate(TNode<T>* x)
{
    TNode<T>* y = x->right;
    TNode<T>* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
        height(x->right)) +
        1;
    y->height = max(height(y->left),height(y->right)) +
        1;
    return y;

}
template<class T>
int AVLTree<T>::BalanceFactor(TNode<T>* N) {
    if (N == NULL)
        return 0;
    return height(N->left)-height(N->right);
}

template<class T>
TNode<T>* AVLTree<T>::insertNode(TNode<T>* node, T k) {
    // Find the correct dpostion and insert the node
    if (node == NULL)
    {
        TNode<T>* r = new TNode<T>(k, NULL, NULL);
        r->data = k;
        r->left = NULL;
        r->right = NULL;
        r->height = 1;
        return r;
    }
    if (k < node->data)
        node->left = insertNode(node->left, k);
    else if (k > node->data)
        node->right = insertNode(node->right, k);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + max(height(node->left),
        height(node->right));
    int balanceFactor = BalanceFactor(node);
    if (balanceFactor > 1) {
        if (k < node->left->data) {
            return rightRotate(node);
        }
        else if (k> node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (k > node->right->data) {
            return leftRotate(node);
        }
        else if (k < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;

}

template<class T>
TNode<T>* AVLTree<T>::nodeWithMimumValue(TNode<T>* node) {
    TNode<T>* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}
template<class T>
TNode<T>* AVLTree<T>::deleteNode(TNode<T>* root, T k){

    // Find the node and delete it
    if (root == NULL)
        return root;
    if (k < root->data)
        root->left = deleteNode(root->left, k);
    else if (k > root->data)
        root->right = deleteNode(root->right, k);
    else {
        if ((root->left == NULL) ||
            (root->right == NULL)) {
            TNode<T>* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            TNode<T>* temp = nodeWithMimumValue(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right,
                temp->data);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left),
        height(root->right));
    int balanceFactor = BalanceFactor(root);
    if (balanceFactor > 1) {
        if (BalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (BalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}
template<class T>
void AVLTree<T>::printTree(TNode<T>* root, string indent, bool last){
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        }
        else {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->data << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }



}
template<class T>
void AVLTree<T>::print2D(TNode<T>* r, int space) {

    if (r == NULL)
        return;
    space += SPACE;
    print2D(r->right, space);
    std::cout << std::endl;
    for (int i = SPACE; i < space; i++)
        std::cout << " ";
    std::cout << r->data << "\n";
    print2D(r->left, space);
}


