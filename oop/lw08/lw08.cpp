// NewLw02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include "Rectangle.h"
#include "Rhombus.h"
#include "Trapeze.h"
#include "TreeItem.h"
#include "Tree.h"
#include <memory>

int main()
{
	Tree<Figure> tree;
	std::shared_ptr<TreeItem<Figure>> test;
	std::shared_ptr<Figure> ptr;
	size_t input = 0, key, parentKey;
	std::cout << "Choose an operation:" << std::endl;
	std::cout << "1) Add trapeze" << std::endl;
	std::cout << "2) Add rhomb" << std::endl;
	std::cout << "3) Add rectangle" << std::endl;
	std::cout << "4) Delete node from tree" << std::endl;
	std::cout << "5) Print tree" << std::endl;
	std::cout << "6) Exit" << std::endl;
	std::cout << "7) Iterator demo" << std::endl;
	std::cout << "8) Sort demo" << std::endl;
	std::cout << "9) Parallel sort demo" << std::endl;
	std::cout << "Insert: sides, key, parent key" << std::endl;
	while (input != 6) {
		std::cin >> input;
		if (input == 1) {
			ptr = std::make_shared<Trapeze>(std::cin);
			std::cin >> key >> parentKey;
			tree.insert(ptr, parentKey, key);
		}
		else if (input == 2) {
			ptr = std::make_shared<Rhombus>(std::cin);
			std::cin >> key >> parentKey;
			tree.insert(ptr, parentKey, key);
		}
		else if (input == 3) {
			ptr = std::make_shared<Rectangle>(std::cin);
			std::cin >> key >> parentKey;
			tree.insert(ptr, parentKey, key);
		}
		else if (input == 4) {
			if (!tree.empty()) {
				std::cin >> key;
				tree.remove(key);
			}
			else {
				std::cout << "Tree is empty." << std::endl;
			}

		}
		else if (input == 5) {
			if (!tree.empty())
				tree.print();
			else {
				std::cout << "Tree is empty." << std::endl;
			}
		}
		else if (input == 7) {
			if (tree.empty())
				std::cout << "Tree is empty" << std::endl;
			else {
				for (auto i : tree) {
					i->print();
					std::cout << std::endl;
				}
			}
		}
		else if (input == 8) {
			if (tree.empty())
				std::cout << "Tree is empty" << std::endl;
			else {
				tree.sort();
			}
		}
		else if (input == 9) {
			if (tree.empty())
				std::cout << "Tree is empty" << std::endl;
			else {
				tree.sortParallel();
			}
		}
	}
	system("pause");
	return 0;
}

