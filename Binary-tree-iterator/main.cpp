#include <iostream>
#include <functional>
#include "BinaryTree.hpp"
#include <ctime>
#include <cstdlib>

int compareIntValues(int a, int b)
{
	return a - b;
}

int main(void)
{
	std::function<int(int, int)> func = compareIntValues;
	BinaryTree<int> *tree = new BinaryTree<int>(func);
	srand(time(nullptr));

	int _rand = 0;
	for (size_t i = 0; i < 12; i++)
	{
		_rand = rand() % 10000 + 1;
		std::cout << "Nahodna generovana hodnota je: " << _rand << std::endl;
		tree->insert(_rand);
	}

	auto it = tree->begin();

	while (!it)
	{
		std::cout << it.currentKey() << std::endl;
		it++;
	} 

	BinaryTree<int> *bst = new BinaryTree<int>(func);

	auto iterator = bst->begin();

	std::cout << iterator.currentKey() << std::endl;

	system("pause");
	return 0;
}