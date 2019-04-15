#pragma once

#include <fstream>
#include <functional>
#include "Queue.hpp"
 
using namespace ADSLibrary::DataStructures::LinkedStructures::OOP;

template<class T>
class BinaryTree
{
public:
	class Node;
	class Iterator
	{
	public:
		friend class BinaryTree<T>;
		void reset();
		const T & currentKey() const;
		void next();
		bool isEnd() const;
		~Iterator();
		Iterator & operator++();
		Iterator & operator++(int);
		inline bool operator!() const { return !isEnd(); }

	private:
		Iterator(const BinaryTree<T> * const &);
		BinaryTree<T> const * tree;
		Queue<BinaryTree<T>::Node*> *queue = nullptr;
	};

	BinaryTree(const std::function<int(T, T)> &);
	~BinaryTree();
	void insert(const T &);
	BinaryTree<T>::Iterator & begin(void) const;
	void exportDOT() const;

private:

	class Node
	{
	public:
		Node(const T &);
		~Node();
		T key;
		Node *left = nullptr;
		Node *right = nullptr;
	};

	void exportDOT(std::ofstream & file, Node *, int counter = 0) const;
	void insert(const T &, Node *&);

	std::function<int(T, T)> comparator;
	Node * root = nullptr;

};

template<class T>
BinaryTree<T>::BinaryTree(const std::function<int(T, T)> & func)
{
	comparator = func;
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
	if (root != nullptr) {
		delete root;
		root = nullptr; 
	}
}

template<class T>
void BinaryTree<T>::insert(const T & data)
{
	this->insert(data, root);
}

template<class T>
typename BinaryTree<T>::Iterator & BinaryTree<T>::begin(void) const
{
	BinaryTree<T>::Iterator *it = new BinaryTree<T>::Iterator(this);
	it->reset();
	return *it;
}

template<class T>
void BinaryTree<T>::exportDOT() const
{
	std::ofstream file("graf.gv", ios::trunc);
	file << "graph {";
	exportDOT(file, root);
	file << "}";
}

template<class T>
void BinaryTree<T>::exportDOT(std::ofstream & file,  Node * root, int counter) const
{

	if (root == nullptr)
		return;
	if (root->left != nullptr)
	{
		file << "    _" << counter << " -- _" << (counter + 1) << std::endl;
		exportDOT(file, root->left, counter + 1);
	}
	if (root->right != nullptr)
	{
		file << "    _" << counter << " -- _" << (counter + 1) << std::endl;
		exportDOT(file, root->right, counter + 1);
	}

}

template<class T>
void BinaryTree<T>::insert(const T & data, Node *& root)
{
	if (root == nullptr)
	{
		root = new Node(data);
		return;
	}
	if (comparator(data, root->key) < 0)
		insert(data, root->left);
	if (comparator(data, root->key) > 0)
		insert(data, root->right);
}

template<class T>
BinaryTree<T>::Node::Node(const T & data)
{
	key = data;
}

template<class T>
BinaryTree<T>::Node::~Node()
{
	if (left != nullptr) { delete left; left = nullptr; }
	if (right != nullptr) { delete right; right = nullptr; }
}

template<class T>
void BinaryTree<T>::Iterator::reset()
{
	queue->Clear();
	queue->Enqueue(tree->root);
}

template<class T>
const T & BinaryTree<T>::Iterator::currentKey() const
{
	return queue->Peek()->key;
}

template<class T>
void BinaryTree<T>::Iterator::next()
{
	auto n = queue->Dequeue();
	if (n->left != nullptr) queue->Enqueue(n->left);
	if (n->right  != nullptr) queue->Enqueue(n->right);
}

template<class T>
bool BinaryTree<T>::Iterator::isEnd() const
{
	return queue->IsEmpty();
}

template<class T>
BinaryTree<T>::Iterator::~Iterator()
{
	//if (tree != nullptr) { delete tree; tree = nullptr; }
	if (queue != nullptr) { delete queue; queue = nullptr; }
}

template<class T>
typename BinaryTree<T>::Iterator & BinaryTree<T>::Iterator::operator++()
{
	next();
	return *this;
}

template<class T>
typename BinaryTree<T>::Iterator & BinaryTree<T>::Iterator::operator++(int)
{
	next();
	return *this;
}

template<class T>
BinaryTree<T>::Iterator::Iterator(const BinaryTree<T> * const & btree)
{
	tree = btree;
	queue = new Queue<Node *>;
}
