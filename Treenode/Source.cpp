#include<iostream>
#include"BST.h"
#include"AVLTree.h"
#include"RedBlackTree.h"
#include"GeneralTree.h"
int main()
{
	/*
	tree t;
	t.insert(-1, 5);
	t.insert(5, 2);
	t.insert(5, 7);
	t.insert(5, 8);
	t.insert(5, 4);
	t.insert(5, 3);
	gnode* v = t.search(-1, t.root);
	(*v->children).print();
	t.insert(7, 12);
	t.insert(7, 14);
	gnode* q = t.search(7, t.root);
	(*q->children).print();
	t.insert(14, 42);
	t.insert(14, 69);
	gnode* r = t.search(14, t.root);
	(*r->children).print();
	

*/



	/*

	BST<int>Alp;
	int a = 25;
	int b = 12;
	int c = 30;
	int d = 35;
	int e = 13;
	int f = 12;
	int g = 29;
	Alp.insert(a);
	Alp.insert(b);
	Alp.insert(c);
	Alp.insert(d);
	Alp.insert(e);
	Alp.insert(f);
	Alp.insert(g);		///Alltwins function is used to check a perfect bst
	bool pq=Alp.allTwins();
	if (pq == 1)
	{
		cout << "Tree is perfect\n";
	}
	else {
		cout << "Tree is not perfect";
	}
	Alp.inOrderDFT();
	Alp.print2D(Alp.getRoot(), 10);
	Alp.deleteNode(Alp.getRoot(), 29);
	Alp.print2D(Alp.getRoot(), 10);
	*/
	//****//////////////////////////////
	
	//AVL Tree Portion
	// AVLTree<int>bet(50);
//	TNode<int>* root = NULL;

	// 
	//bet.insertNode(root, 33);
	//root = bet.insertNode(root, 13);
	//root = bet.insertNode(root, 53);
	//root = bet.insertNode(root, 9);
	//root = bet.insertNode(root, 21);
	//root = bet.insertNode(root, 61);
	//root = bet.insertNode(root, 8);
	//root = bet.insertNode(root, 11);
	//bet.deleteNode(root, 13);

	//cout << "AVL Tree is ";
	//bet.print2D(root,10);
	//bet.printTree(root," ",true);
	///******************///
	//Red Black Tree Example
		//RedBlackTree<int> bst;
		//bst.insert(55);
		//bst.insert(40);
		//bst.insert(65);
		//bst.insert(60);
		//bst.insert(75);
		//bst.insert(57);
		//bst.printTree();
		//cout << endl
		//	<< "deleting gives us as" << endl;
		//bst.deleteNode(40);
		//bst.printTree();
		//bst.print2D(bst.getRoot(), 5);
	

	return 0;



}