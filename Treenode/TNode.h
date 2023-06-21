#ifndef TNODE_HEADER_FILE
#define TNODE_HEADER_FILE

template <class T> class BST;
template <class T> class AVLTree;

template <class T>
class TNode {
private:
	T data;
	TNode* left;
	TNode* right;
	int depth;
	int height;
	friend class BST<T>;
	friend class AVLTree<T>;
public:
	TNode(T& v, TNode* left, TNode* right);
	~TNode() {};
	T getData() { return data; }
	TNode* getLeft() { return left; }
	TNode* getRight() { return right; }
};

template <class T>
TNode<T>::TNode(T& v, TNode* left, TNode* right) {
	data = v;
	this->left = left;
	this->right = right;
	depth = height = -1; // Not computed yet
}

#endif