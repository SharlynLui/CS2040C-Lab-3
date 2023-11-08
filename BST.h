#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode {
private:
	T _item;
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	int _height;
	int _weight;
public:
	TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0; };
	friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree {
protected:
	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withHeight);

	// The following functions are optional for you to implement. 
	TreeNode<T>*  _insert(TreeNode<T>* current, T x);
	void _inOrderPrint(TreeNode<T>*);
	void _postOrderPrint(TreeNode<T>*);
	void _preOrderPrint(TreeNode<T>*);
	TreeNode<T>* _rightRotation(TreeNode<T>*);
	TreeNode<T>* _leftRotation(TreeNode<T>*);
	TreeNode<T>* _searchMax(TreeNode<T>*);
	TreeNode<T>* _searchMin(TreeNode<T>*);
	TreeNode<T>* _search(TreeNode<T>*, T);
	void _destroySubTree(TreeNode<T>*);
	T _addWeight(TreeNode<T>*);

public:
	BinarySearchTree() { _root = NULL; _size = 0; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withHeight = 1);
	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();
	T searchMax() { return _searchMax(_root)->_item; }
	T searchMin() { return _searchMin(_root)->_item; }
	bool exist(T x);
	T search(T x) { return T(); };
	T successor(T);
};

template <class T>
T BinarySearchTree<T>::_addWeight(TreeNode<T>* current) {
	//no child
	if (!current->_left && !current->_right) {
		return 1;
	}
	//right child only
	if (!current->_left) {
		return (current->_right->_weight + 1);
	}
	//left child only
	if (!current->_right) {
		return (current->_left->_weight + 1);
	}
	//both child
	return (current->_left->_weight + current->_right->_weight + 1);
}

template <class T>
void BinarySearchTree<T>::insert(T x)
{
	_root = _root ? _insert(_root, x) : new TreeNode<T>(x);
	_size++;
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withHeight) {

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withHeight);
	for (int i = 0; i < indent; i++)
		cout << "  ";
	cout << node->_item;
	if (withHeight)
		cout << "(h=" << node->_height << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withHeight);


};

template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
	_printTree(0, _root, withHeight);
}


template <class T>
void BinarySearchTree<T>::preOrderPrint() {

	_preOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	cout << node->_item << " ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T> ::_destroySubTree(TreeNode<T>* node)
{
	if (node->_left)
		_destroySubTree(node->_left);
	if (node->_right)
		_destroySubTree(node->_right);
	delete node;
}

template <class T>
BinarySearchTree<T> :: ~BinarySearchTree()
{
	if (_root)
		_destroySubTree(_root);
}



template <class T>
void BinarySearchTree<T>::inOrderPrint() {
	_inOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
	if (!node) {
		return;
	}
	_inOrderPrint(node->_left);
	cout << node->_item << " ";
	_inOrderPrint(node->_right);
}

template <class T>
void BinarySearchTree<T>::postOrderPrint() {
	_postOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
	if (!node) {
		return;
	}
	_postOrderPrint(node->_left);
	_postOrderPrint(node->_right);
	cout << node->_item << " ";
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {


	if (current->_item > x)
	{
		if (current->_left)
			current->_left = _insert(current->_left, x);
		else
		{
			current->_left = new TreeNode<T>(x);
		}
	}
	else if (x > current->_item) {
		if (current->_right)
			current->_right = _insert(current->_right, x);
		else
		{
			current->_right = new TreeNode<T>(x);
		}
	}
	else
		return current; // When the node already existed in the tree

	current->_height = max(current->_left ? current->_left->_height : -1, current->_right ? current->_right->_height : -1) + 1;
	current->_weight = _addWeight(current);
	cout << current->_item << ":" << current->_weight << ", ";
	return current;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMax(TreeNode<T>* current) {
	while (current->_right) {
		current = current->_right;
	}
	return current;
}


template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMin(TreeNode<T>* current) {
	while (current->_left) {
		current = current->_left;
	}
	return current;
}

template <class T>
bool BinarySearchTree<T>::exist(T x) {
	TreeNode<T>* current = _root;
	while (current) {
		if (x == current->_item) {
			return true;
		}
		if (x > current->_item) {
			current = current->_right;
		}
		else {
			current = current->_left;
		}
	}
	return false;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_search(TreeNode<T>* current, T x) {
	return NULL;
}

template <class T>
T BinarySearchTree<T>::successor(T x) {
TreeNode<T>* lastleft = _root;
TreeNode<T>* current = _root;
if (x <= searchMin()) {
	return searchMin();
}
if (x >= searchMax()) {
	return searchMax();
}
while (current) {
	if (x == current->_item) {
		break; //ensures that current points at the key
	}
	if (x > current->_item) {
		current = current->_right;
	}
	if (x < current->_item) {
		lastleft = current;
		current = current->_left;
	}
}
if (current != NULL && current->_right) {
	return _searchMin(current->_right)->_item;
}
return lastleft->_item; //if not found in tree or has no right child
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* node)
{
	return node;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* node)
{
	return node;
}
