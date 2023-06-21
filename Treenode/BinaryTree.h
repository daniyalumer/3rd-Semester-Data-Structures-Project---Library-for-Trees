#pragma once
#include "TNode.h"
#define SPACE 10
template <class T>
class BinaryTree {
private:
	TNode<T>* root;

public:
	BinaryTree() { root = nullptr; }		///Just an interface class to define a BST/AVL and RedBlack Tree
	~BinaryTree() { clearAll(); }
	TNode<T>* getRoot() { return root; }
	bool isEmpty(void);
	bool search(T& val);
	void insert(TNode<T>* R,T& val);
	void inOrderDFT() { inOrderDFT(root); }
	void preOrderDFT() { preOrderDFT(root); }
	void postOrderDFT() { postOrderDFT(root); }
	void clearAll() { clearAll(root);	root = nullptr; }
	void computeDepth() { computeNodeDepths(root, nullptr); }
	void computeHeight() { computeNodeHeights(root); }
	bool  CheckGivenLevel(TNode<T>* r, int level);
	TNode<T>* minValueNode(TNode<T>* node);
	bool allTwins();
	
	TNode<T>* deleteNode(TNode<T>* r, int v);
	void print2D(TNode<T>* r, int space);
};

