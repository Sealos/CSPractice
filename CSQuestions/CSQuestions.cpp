#include "stdafx.h"


int main()
{
	auto tree = BinarySearchTree<int>();
	tree.insert(5);
	tree.insert(4);
	tree.insert(7);
	tree.insert(6);
	tree.insert(2);
	tree.insert(1);
	tree.insert(9);
	tree.insert(40);

	tree.print();
	std::cout << std::endl;
	tree.print_in_order();
	std::cout << std::endl;
	tree.exists(5);
	tree.remove(5);
	std::cout << std::endl;
	tree.print();
    return 0;
}

