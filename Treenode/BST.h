#include "TNode.h"
#include"BinaryTree.h"
#define SPACE 10
template <class T>
class BST :public BinaryTree<T>{
private:
	TNode<T>* root;
	void inOrderDFT(TNode<T>* c);
	void preOrderDFT(TNode<T>* c);
	void postOrderDFT(TNode<T>* c);
	void clearAll(TNode<T>* c);
	void computeNodeHeights(TNode<T>* c);
	void computeNodeDepths(TNode<T>* n, TNode<T>* parent);

public:
	BST() { root = nullptr; }
	~BST() { clearAll(); }
	TNode<T>* getRoot() { return root; }
	bool isEmpty(void);
	bool search(T& val);
	void insert(T& val); 
	void inOrderDFT() { inOrderDFT(root); }
	void preOrderDFT() { preOrderDFT(root); }
	void postOrderDFT() { postOrderDFT(root); }
	void clearAll() { clearAll(root);	root = nullptr; }
	void computeDepth() { computeNodeDepths(root, nullptr); }
	void computeHeight() { computeNodeHeights(root); }
	bool  CheckGivenLevel(TNode<T>* r, int level);
	TNode<T>* minValueNode(TNode<T>* node);

	int sum(TNode<T>* root);
	bool allTwins();
	void happyBST();
	
	TNode<T>* deleteNode(TNode<T>* r, int v);
	void print2D(TNode<T>* r, int space);
};

template <class T>
bool BST<T>::isEmpty() {
	return root == nullptr;
}

//You should not be using function insert in your solution
//You need implement a new version of insert in Ex1
template <class T>
void BST<T>::insert(T& val) {
	TNode<T>* newNode = new TNode<T>(val, nullptr, nullptr);
	if (isEmpty()) { root = newNode; return; }
	TNode<T>* p = nullptr;
	TNode<T>* c = root;
	while (c != nullptr) {
		p = c;
		if (val > c->data) c = c->right; else c = c->left;
	}
	if (val > p->data) p->right = newNode; else p->left = newNode;
}

template <class T>
void BST<T>::inOrderDFT(TNode<T>* c) {
	if (c == nullptr) return;
	inOrderDFT(c->left);
	std::cout << c->data << ", ";
	inOrderDFT(c->right);
}

template <class T>
void BST<T>::postOrderDFT(TNode<T>* c) {
	if (c == nullptr) return;
	postOrderDFT(c->left);
	postOrderDFT(c->right);
	std::cout << c->data << ", ";
}

template <class T>
void BST<T>::preOrderDFT(TNode<T>* c) {
	if (c == nullptr) return;
	std::cout << c->data << ", ";
	preOrderDFT(c->left);
	preOrderDFT(c->right);
}

template <class T>
bool BST<T>::search(T& val) {
	TNode<T>* c = root;
	while (c != nullptr) {
		if (val == c->data)
			return true;
		if (val <= c->data)
			c = c->left;
		else
			c = c->right;
	}
	return false;
}

template <class T>
void BST<T>::clearAll(TNode<T>* c) {
	if (c == nullptr) return;

	clearAll(c->left);
	clearAll(c->right);
	delete c;
}

template <class T>
void BST<T>::computeNodeHeights(TNode<T>* c) {
	if (c == nullptr)  return;
	computeNodeHeights(c->left);
	computeNodeHeights(c->right);
	int  leftH = -1;
	if (c->left != nullptr)
		leftH = c->left->height;
	int rightH = -1;
	if (c->right != nullptr)
		rightH = c->right->height;
	if (leftH > rightH)
		c->height = leftH + 1;
	else
		c->height = rightH + 1;
}

template <class T>
void BST<T>::computeNodeDepths(TNode<T>* n, TNode<T>* parent) {
	if (n == nullptr)   return;
	if (n == root)   n->depth = 0;
	else
		n->depth = parent->depth + 1;
	computeNodeDepths(n->left, n);
	computeNodeDepths(n->right, n);
}
template<class T>
bool BST<T>::CheckGivenLevel(TNode<T>* r, int level) {
	bool a;						//This function actually check that at given level all the nodes are twins or not
	bool b;

	if (r->left == NULL && r->right == NULL)
		return true;					//Exit condition for recursion
	else if (level == 0)
	{
		if (r->left == NULL && r->right == NULL || r->left != NULL && r->right != NULL)
		{
			return true;				//If both sides are null that mean leaf node have no children
		}
		if (r->left == NULL && r->right != NULL || r->right == NULL && r->left != NULL)
		{
			return false;				//If either left or right is null and other is not null this means that it had one children ,not twins
		}
	}
	else // level > 0  
	{
		a = CheckGivenLevel(r->left, level - 1); //Recursive call to left of root node
		if (!a) {
			return false;
		}
		b = CheckGivenLevel(r->right, level - 1);
		if (!b) {
			return false;					//Recursive call to right of root node
		}
	}
}
template<class T>
inline TNode<T>* BST<T>::minValueNode(TNode<T>* node)
{		TNode<T>* current = node;
		/* loop down to find the leftmost leaf */
		while (current->left != NULL) {
			current = current->left;
		}
		return current;
}
template<class T>
bool BST<T>::allTwins() {
	computeNodeHeights(root);			//Compute the height of the tree
	int h = root->height;					
	bool a;
	for (int i = 0; i <= h; i++)
	{
		a = CheckGivenLevel(root, i);	//BFS to check if all nodes are twin or not
		if (!a) {

			return false;	//If any nodes are not twins it return false.
		}
	}
	
	return true;	 //Otherwisse it return true

}

template<class T>
void BST<T>::happyBST() {
	bool a;						//This function checks if a BST is happy i.e perfect and its left most value-rightmost=root

	a = false;							
	if (!this->allTwins())		
	{
		std::cout << "This is not a happy BST\n";	//First of all we check if it is perfect subtree
}													//If all the nodes are twins except leavenode then it will be perfect
	if (root == NULL) {											
		std::cout << "This is not a happy BST!\n";       //Check if the root is null then it is an Empty BST
	}
	else {
		TNode<T>* temp = root->left;					//Two temporary nodes to check left most and right most nodes
		TNode<T>* temp1 = root->right;
		while (temp != NULL && temp1 != NULL) {			//While loop to check all the nodes till the leafnode
			if (std::abs(temp->data - temp1->data) == root->data)//If left most node-rightmost= root node the it is Happy BST
			{
				a = true;
				std::cout << "Happy BST!\n";
				break;
			}
			temp = temp->left;							//If not then it checks for the next left and right nodes
			temp1 = temp1->right;
		}
	}
	if (!a) {
		std::cout << "This is not a Happy BST\n";//If a is not true then it is not the happy BST
	}

}
template<class T>
inline TNode<T>* BST<T>::deleteNode(TNode<T>* r, int v)
{
		// base case 
		if (r == NULL) {
			return NULL;
		}
		// If the key to be deleted is smaller than the root's key, 
		// then it lies in left subtree 
		else if (v < r->data) {
			r->left = deleteNode(r->left, v);
		}
		// If the key to be deleted is greater than the root's key, 
		// then it lies in right subtree 
		else if (v > r->data) {
			r->right = deleteNode(r->right, v);
		}
		// if key is same as root's key, then This is the node to be deleted 
		else {
			// node with only one child or no child 
			if (r->left == NULL) {
				TNode<T>* temp = r->right;
				delete r;
				return temp;
			}
			else if (r->right == NULL) {
				TNode<T>* temp = r->left;
				delete r;
				return temp;
			}
			else {
				// node with two children: Get the inorder successor (smallest 
				// in the right subtree) 
				TNode<T>* temp = minValueNode(r->right);
				// Copy the inorder successor's content to this node 
				r->data = temp->data;
				// Delete the inorder successor 
				r->right = deleteNode(r->right, temp->data);
				//deleteNode(r->right, temp->value); 
			}
		}
		return r;
	}


template<class T>
inline void BST<T>::print2D(TNode<T>* r, int space)
{
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
template<class T>
int BST<T>:: sum(TNode<T>* root)
{
	if (root == NULL)				//Exit condition for recursion
		return 0;

	return sum(root->left) + root->data +		//Recursive call 
		sum(root->right);						//Returns sum of the left subtreee
}
