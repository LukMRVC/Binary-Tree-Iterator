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

	for (size_t i = 0; i < 100; i++)
	{
		tree->insert(rand() % 10000 + 1);
	}

	auto it = tree->begin();
	
	//tree->exportDOT();

	while (!it)
	{
		std::cout << it.currentKey() << std::endl;
		it++;
	} 

	system("pause");
	return 0;
}