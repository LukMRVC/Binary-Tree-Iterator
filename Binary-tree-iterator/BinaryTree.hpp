#pragma once

#include <fstream>
#include <functional>
#include "Queue.hpp"
 
using namespace ADSLibrary::DataStructures::LinkedStructures::OOP;

template<class T>
class BinaryTree
{

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
	void exportDOT(std::ofstream & file, Node *) const;
	void insert(const T &, Node *&);
	std::function<int(T, T)> comparator;
	Node * root = nullptr;
public:
	class Iterator
	{
	public:
		void reset();
		const T & currentKey() const;
		void next();
		bool isEnd() const;
		~Iterator();
		Iterator & operator++();
		Iterator & operator++(int);
		inline bool operator!(void) const { return !isEnd();  }
		
	private:
		Iterator(const BinaryTree<T> * const &);
		BinaryTree<T> const * tree;
		Queue<BinaryTree<T>::Node*> *queue = nullptr;
		friend BinaryTree<T>::Iterator & BinaryTree<T>::begin(void) const;
	};

	BinaryTree(const std::function<int(T, T)> &);
	~BinaryTree();
	void insert(const T &);
	BinaryTree<T>::Iterator & begin(void) const;
	void exportDOT() const;
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
	file << "graph {" << std::endl;
	exportDOT(file, root);
	file << "}";
}

template<class T>
void BinaryTree<T>::exportDOT(std::ofstream & file,  Node * root) const
{

	if (root == nullptr)
		return;
	if (root->left != nullptr)
	{
		file << "    _" << root->key << " -- _" << (root->left->key) << std::endl;
		exportDOT(file, root->left);
	}
	if (root->right != nullptr)
	{
		file << "    _" << root->key << " -- _" << (root->right->key) << std::endl;
		exportDOT(file, root->right);
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
	queue->Enqueue(tree->root);
}

template<class T>
const T & BinaryTree<T>::Iterator::currentKey() const
{
	return (queue->Peek() != nullptr) ? queue->Peek()->key : INT32_MAX;
}

template<class T>
void BinaryTree<T>::Iterator::next()
{
	auto n = queue->Dequeue();
	if (n->left != nullptr) queue->Enqueue(n->left);
	if (n->right != nullptr) queue->Enqueue(n->right);
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
